/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rast_tri.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 15:29:06 by babonnet          #+#    #+#             */
/*   Updated: 2024/06/01 18:47:37 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_data.h"
#include <stdint.h>
#include <immintrin.h>
#include <math.h>
#include <mlx.h>  // Ensure the correct path for mlx.h based on your project setup
#include <strings.h>

#define NR_PLANES 3
#define PIPE_MAX_COLOR_BUFS 8
#define BLOCK_SIZE 4

#define RIGHT_MASK_TAB_16 { \
    0xFFFFFFFF,             \
    0x0000FFFF,             \
    0x000000FF,             \
    0x0000000F              \
}

#define BOTTOM_MASK_TAB_16 { \
    0xFFFFFFFF,             \
    0xFFFF0000,             \
    0xFF000000,             \
    0x0F000000              \
}

struct t_vec3 {
    float x, y, z;
};

struct t_vertex {
    struct t_vec3 position;
};

typedef struct t_tri {
    struct t_vertex vertex1;
    struct t_vertex vertex2;
    struct t_vertex vertex3;
} t_tri;

struct lp_rast_shader_inputs {
    unsigned frontfacing:1;
    unsigned disable:1;
    unsigned is_blit:1;
    unsigned viewport_index:4;
    unsigned layer:11;
    unsigned view_index:14;
    unsigned stride;
    unsigned pad[2];
};

struct lp_rast_plane {
    int64_t c;
    int32_t dcdx;
    int32_t dcdy;
    uint32_t eo;
    uint32_t pad;
};

struct lp_rasterizer_task {
    const struct cmd_bin *bin;
    const struct lp_rast_state *state;
    struct lp_scene *scene;
    unsigned x, y;
    unsigned width, height;
    uint8_t *color_tiles[PIPE_MAX_COLOR_BUFS];
    uint8_t *depth_tile;
    struct lp_rasterizer *rast;
    unsigned thread_index;
    unsigned occlude;
};

struct lp_rast_triangle {
    struct lp_rast_shader_inputs inputs;
};

union lp_rast_cmd_arg {
    const struct lp_rast_shader_inputs *shade_tile;
    struct {
        const struct lp_rast_triangle *tri;
        unsigned plane_mask;
    } triangle;
    const struct lp_rast_rectangle *rectangle;
    const struct lp_rast_state *set_state;
    const struct lp_rast_clear_rb *clear_rb;
    struct {
        uint64_t value;
        uint64_t mask;
    } clear_zstencil;
    struct lp_fence *fence;
    struct llvmpipe_query *query_obj;
};

static inline struct lp_rast_plane *GET_PLANES(const struct lp_rast_triangle *tri) {
    const uint8_t *p = (const uint8_t *)(&tri->inputs + 1);
    return (struct lp_rast_plane *)(p + 3 * tri->inputs.stride);
}

static inline unsigned sign_bits4(const __m128i *cstep, int cdiff) {
    __m128i cio4 = _mm_set1_epi32(cdiff);
    __m128i cstep0 = _mm_add_epi32(cstep[0], cio4);
    __m128i cstep1 = _mm_add_epi32(cstep[1], cio4);
    __m128i cstep2 = _mm_add_epi32(cstep[2], cio4);
    __m128i cstep3 = _mm_add_epi32(cstep[3], cio4);
    __m128i cstep01 = _mm_packs_epi32(cstep0, cstep1);
    __m128i cstep23 = _mm_packs_epi32(cstep2, cstep3);
    __m128i result = _mm_packs_epi16(cstep01, cstep23);
    return _mm_movemask_epi8(result);
}

void custom_shade_quads_mask(struct lp_rasterizer_task *task, const struct lp_rast_shader_inputs *inputs, int px, int py, unsigned mask, int zbuffer[HEIGHT][WIDTH], unsigned int color, t_mlx *mlx) {
    for (int iy = 0; iy < 4; iy++) {
        for (int ix = 0; ix < 4; ix++) {
            if (mask & (1 << (iy * 4 + ix))) {
                int x = px + ix;
                int y = py + iy;
                if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT) {
                    if (inputs->layer < zbuffer[y][x]) {
                        zbuffer[y][x] = inputs->layer;
                        mlx_pixel_put(mlx->connection, mlx->window, x, y, color);
                    }
                }
            }
        }
    }
}

void TRI_16(struct lp_rasterizer_task *task, const union lp_rast_cmd_arg arg, int zbuffer[HEIGHT][WIDTH], unsigned int color, t_mlx *mlx) {
    const struct lp_rast_triangle *tri = arg.triangle.tri;
    const struct lp_rast_plane *plane = GET_PLANES(tri);
    unsigned mask = arg.triangle.plane_mask;
    __m128i cstep4[NR_PLANES][4];
    int x = (mask & 0xff);
    int y = (mask >> 8);
    unsigned outmask = 0;
    static const uint32_t right_mask_tab[] = RIGHT_MASK_TAB_16;
    static const uint32_t bottom_mask_tab[] = BOTTOM_MASK_TAB_16;

    if (x + 12 >= 64) {
        int i = ((x + 12) - 64) / 4;
        outmask |= right_mask_tab[i];
    }

    if (y + 12 >= 64) {
        int i = ((y + 12) - 64) / 4;
        outmask |= bottom_mask_tab[i];
    }

    x += task->x;
    y += task->y;

    for (unsigned j = 0; j < NR_PLANES; j++) {
        const int dcdx = -plane[j].dcdx * 4;
        const int dcdy = plane[j].dcdy * 4;
        __m128i xdcdy = _mm_set1_epi32(dcdy);

        cstep4[j][0] = _mm_setr_epi32(0, dcdx, dcdx * 2, dcdx * 3);
        cstep4[j][1] = _mm_add_epi32(cstep4[j][0], xdcdy);
        cstep4[j][2] = _mm_add_epi32(cstep4[j][1], xdcdy);
        cstep4[j][3] = _mm_add_epi32(cstep4[j][2], xdcdy);

        const int c = plane[j].c + plane[j].dcdy * y - plane[j].dcdx * x;
        const int cox = plane[j].eo * 4;

        outmask |= sign_bits4(cstep4[j], c + cox);
    }

    if (outmask == 0xffff)
        return;

    unsigned partial_mask = 0xffff & ~outmask;

    while (partial_mask) {
        int i = ffs(partial_mask) - 1;
        int ix = (i & 3) * 4;
        int iy = (i >> 2) * 4;
        int px = x + ix;
        int py = y + iy;
        unsigned mask = 0xffff;

        partial_mask &= ~(1 << i);

        for (unsigned j = 0; j < NR_PLANES; j++) {
            const int cx = (plane[j].c - 1
                            - plane[j].dcdx * px
                            + plane[j].dcdy * py) * 4;

            mask &= ~sign_bits4(cstep4[j], cx);
        }

        if (mask)
            custom_shade_quads_mask(task, &tri->inputs, px, py, mask, zbuffer, color, mlx);
    }
}

void rast_tri(t_tri triangle, t_mlx *mlx, unsigned int color, int zbuffer[HEIGHT][WIDTH]) {
    struct lp_rasterizer_task task;
    struct lp_rast_triangle tri;
    struct lp_rast_plane planes[NR_PLANES];
    union lp_rast_cmd_arg arg;

    // Initialize rasterizer task properties
    task.width = WIDTH;
    task.height = HEIGHT;
    task.color_tiles[0] = NULL;  // Adjust if using multiple color buffers
    task.depth_tile = NULL;     // Adjust if using a depth buffer
    task.scene = NULL;          // Adjust if part of a larger scene context

    // Calculate the bounding box of the triangle
    int min_x = fmin(triangle.vertex1.position.x, fmin(triangle.vertex2.position.x, triangle.vertex3.position.x));
    int max_x = fmax(triangle.vertex1.position.x, fmax(triangle.vertex2.position.x, triangle.vertex3.position.x));
    int min_y = fmin(triangle.vertex1.position.y, fmin(triangle.vertex2.position.y, triangle.vertex3.position.y));
    int max_y = fmax(triangle.vertex1.position.y, fmax(triangle.vertex2.position.y, triangle.vertex3.position.y));

    // Clamp to render target dimensions
    min_x = fmax(0, min_x);
    min_y = fmax(0, min_y);
    max_x = fmin(WIDTH, max_x);
    max_y = fmin(HEIGHT, max_y);

    // Define triangle vertices
    tri.inputs.stride = sizeof(struct lp_rast_plane) * NR_PLANES;
	arg.triangle.tri = &tri;

	planes[0].dcdx = triangle.vertex2.position.y - triangle.vertex1.position.y;
    planes[0].dcdy = triangle.vertex1.position.x - triangle.vertex2.position.x;
    planes[0].c = planes[0].dcdx * (-triangle.vertex1.position.y) + planes[0].dcdy * triangle.vertex1.position.x;

    planes[1].dcdx = triangle.vertex3.position.y - triangle.vertex2.position.y;
    planes[1].dcdy = triangle.vertex2.position.x - triangle.vertex3.position.x;
    planes[1].c = planes[1].dcdx * (-triangle.vertex2.position.y) + planes[1].dcdy * triangle.vertex2.position.x;

    planes[2].dcdx = triangle.vertex1.position.y - triangle.vertex3.position.y;
    planes[2].dcdy = triangle.vertex3.position.x - triangle.vertex1.position.x;
    planes[2].c = planes[2].dcdx * (-triangle.vertex3.position.y) + planes[2].dcdy * triangle.vertex3.position.x;

    // Iterate over the bounding box in 4x4 blocks
    for (int y = min_y; y < max_y; y += 4) {
        for (int x = min_x; x < max_x; x += 4) {
            task.x = x;
            task.y = y;

            // Prepare the argument for TRI_16
            // Call TRI_16 to rasterize the current 4x4 block of the triangle
            TRI_16(&task, arg, zbuffer, color, mlx);
        }
    }
}
