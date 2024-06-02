/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rast_tri.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 15:29:06 by babonnet          #+#    #+#             */
/*   Updated: 2024/06/02 21:33:43 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <math.h>
#include "mesh_obj.h"
#include "miniRT.h"
#include "mlx.h"
#include "mlx_data.h"
#include "print_int.h"

t_tri mesh_to_triangle(t_mesh mesh, t_point point[3])
{
	t_tri triangle;

	triangle.vertex1.position = mesh.vertex[point[0].vertex].vec3;
	triangle.vertex2.position = mesh.vertex[point[1].vertex].vec3;
	triangle.vertex3.position = mesh.vertex[point[2].vertex].vec3;
	return (triangle);
}

#if defined(__AVX2__)
#include <immintrin.h>

static inline unsigned
build_mask_linear(int c, int dcdx, int dcdy)
{
   __m128i cstep0 = _mm_setr_epi32(c, c+dcdx, c+dcdx*2, c+dcdx*3);
   __m128i xdcdy = _mm_set1_epi32(dcdy);

   /* Get values across the quad
    */
   __m128i cstep1 = _mm_add_epi32(cstep0, xdcdy);
   __m128i cstep2 = _mm_add_epi32(cstep1, xdcdy);
   __m128i cstep3 = _mm_add_epi32(cstep2, xdcdy);

   /* pack pairs of results into epi16
    */
   __m128i cstep01 = _mm_packs_epi32(cstep0, cstep1);
   __m128i cstep23 = _mm_packs_epi32(cstep2, cstep3);

   /* pack into epi8, preserving sign bits
    */
   __m128i result = _mm_packs_epi16(cstep01, cstep23);

   /* extract sign bits to create mask
    */
   return _mm_movemask_epi8(result);
}

#else

unsigned build_mask_linear(int32_t c, int32_t dcdx, int32_t dcdy) 
{
    unsigned int mask;
    int32_t c0 = c;
    int32_t c1 = c0 + dcdy;
    int32_t c2 = c1 + dcdy;
    int32_t c3 = c2 + dcdy;

	mask = 0;
    mask |= ((c0 + 0 * dcdx) >> 31) & (1 << 0);
    mask |= ((c0 + 1 * dcdx) >> 31) & (1 << 1);
    mask |= ((c0 + 2 * dcdx) >> 31) & (1 << 2);
    mask |= ((c0 + 3 * dcdx) >> 31) & (1 << 3);
    mask |= ((c1 + 0 * dcdx) >> 31) & (1 << 4);
    mask |= ((c1 + 1 * dcdx) >> 31) & (1 << 5);
    mask |= ((c1 + 2 * dcdx) >> 31) & (1 << 6);
    mask |= ((c1 + 3 * dcdx) >> 31) & (1 << 7);
    mask |= ((c2 + 0 * dcdx) >> 31) & (1 << 8);
    mask |= ((c2 + 1 * dcdx) >> 31) & (1 << 9);
    mask |= ((c2 + 2 * dcdx) >> 31) & (1 << 10);
    mask |= ((c2 + 3 * dcdx) >> 31) & (1 << 11);
    mask |= ((c3 + 0 * dcdx) >> 31) & (1 << 12);
    mask |= ((c3 + 1 * dcdx) >> 31) & (1 << 13);
    mask |= ((c3 + 2 * dcdx) >> 31) & (1 << 14);
    mask |= ((c3 + 3 * dcdx) >> 31) & (1 << 15);

    return mask;
}
#endif

void do_mask(int mask, int by, int bx, t_mlx *mlx, t_tri triangle, int zbuffer[HEIGHT][WIDTH], int color)
{
	int endy = by  + 4;
	int endx = bx  + 4;
	for (int y = by; y < endy; y++)
	{
		for (int x = bx; x < endx; x++)
		{
			if (mask & 1)
			{
				if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT && triangle.vertex1.position.z < zbuffer[y][x]) {
					zbuffer[y][x] = triangle.vertex1.position.z;
					mlx_pixel_put(mlx->connection, mlx->window, x, y, color);
				}
			}
			mask >>= 1;
		}
	}
}

typedef int __attribute__((vector_size(16), aligned(16))) t__m128i32;

void do_mask_sse(int mask, int by, int bx, t_mlx *mlx, t_tri triangle, int zbuffer[HEIGHT][WIDTH], int color)
{
	const __m128i mask_height = (__m128i)(t__m128i32){HEIGHT - 1, HEIGHT - 1, HEIGHT - 1, HEIGHT - 1};
	const __m128i mask_width = (__m128i)(t__m128i32){WIDTH - 1, WIDTH - 1, WIDTH - 1, WIDTH - 1};
	const __m128i mask_zeros = (__m128i)(t__m128i32){0, 0, 0, 0};

    __m128i mask_x = _mm_setr_epi32(bx, bx + 1, bx + 2, bx + 3);
    __m128i mask_z = _mm_set1_epi32(triangle.vertex1.position.z);

    for (int y = by; y < by + 4; y++) {
        if (y < 0 || y >= HEIGHT) continue;
        __m128i mask_y = _mm_set1_epi32(y);

        __m128i mask_in_bounds_x = _mm_and_si128(_mm_cmpgt_epi32(mask_width, mask_x), _mm_cmpgt_epi32(mask_x, mask_zeros));
        __m128i mask_in_bounds_y = _mm_cmpgt_epi32(mask_y, mask_zeros);
        mask_in_bounds_y = _mm_and_si128(mask_in_bounds_y, _mm_cmpgt_epi32(mask_height, mask_y));

        __m128i z_values = _mm_loadu_si128((__m128i *)&zbuffer[y][bx]);
        __m128i mask_z_check = _mm_cmpgt_epi32(mask_z, z_values);

        __m128i mask_final = _mm_and_si128(mask_in_bounds_x, mask_in_bounds_y);
        mask_final = _mm_and_si128(mask_final, mask_z_check);

	 int results[4];
        _mm_storeu_si128((__m128i*)results, mask_final);
        for (int i = 0; i < 4; i++) {
            if (results[i]) {
                zbuffer[y][bx + i] = triangle.vertex1.position.z;
                mlx_pixel_put(mlx->connection, mlx->window, bx + i, y, color);
            }
        }
		(void)mask;
    }
}

static inline void do_mask_full_sse(int by, int bx, t_mlx *mlx, t_tri triangle, int zbuffer[HEIGHT][WIDTH], int color) {
	const __m128i mask_height = (__m128i)(t__m128i32){HEIGHT - 1, HEIGHT - 1, HEIGHT - 1, HEIGHT - 1};
	const __m128i mask_width = (__m128i)(t__m128i32){WIDTH - 1, WIDTH - 1, WIDTH - 1, WIDTH - 1};
	const __m128i mask_zeros = (__m128i)(t__m128i32){0, 0, 0, 0};

    __m128i mask_x = _mm_setr_epi32(bx, bx + 1, bx + 2, bx + 3);
    __m128i mask_z = _mm_set1_epi32(triangle.vertex1.position.z);

    for (int y = by; y < by + 4; y++) {
        if (y < 0 || y >= HEIGHT) continue;
        __m128i mask_y = _mm_set1_epi32(y);

        __m128i mask_in_bounds_x = _mm_and_si128(_mm_cmpgt_epi32(mask_width, mask_x), _mm_cmpgt_epi32(mask_x, mask_zeros));
        __m128i mask_in_bounds_y = _mm_cmpgt_epi32(mask_y, mask_zeros);
        mask_in_bounds_y = _mm_and_si128(mask_in_bounds_y, _mm_cmpgt_epi32(mask_height, mask_y));

        __m128i z_values = _mm_loadu_si128((__m128i *)&zbuffer[y][bx]);
        __m128i mask_z_check = _mm_cmpgt_epi32(mask_z, z_values);

        __m128i mask_final = _mm_and_si128(mask_in_bounds_x, mask_in_bounds_y);
        mask_final = _mm_and_si128(mask_final, mask_z_check);

	 int results[4];
        _mm_storeu_si128((__m128i*)results, mask_final);
        for (int i = 0; i < 4; i++) {
            if (results[i]) {
                zbuffer[y][bx + i] = triangle.vertex1.position.z;
                mlx_pixel_put(mlx->connection, mlx->window, bx + i, y, color);
            }
        }
    }
}


void rast_tri(t_tri triangle, t_mlx *mlx, unsigned int color, int zbuffer[HEIGHT][WIDTH]) 
{

    // Bounding box
    int min_x = (int)fmin(triangle.vertex1.position.x, fmin(triangle.vertex2.position.x, triangle.vertex3.position.x));
    int min_y = (int)fmin(triangle.vertex1.position.y, fmin(triangle.vertex2.position.y, triangle.vertex3.position.y));
    int max_x = (int)fmax(triangle.vertex1.position.x, fmax(triangle.vertex2.position.x, triangle.vertex3.position.x));
    int max_y = (int)fmax(triangle.vertex1.position.y, fmax(triangle.vertex2.position.y, triangle.vertex3.position.y));

    // Edge function coefficients
    int A12 = triangle.vertex2.position.y - triangle.vertex1.position.y;
    int B12 = triangle.vertex1.position.x - triangle.vertex2.position.x;
    int A23 = triangle.vertex3.position.y - triangle.vertex2.position.y;
    int B23 = triangle.vertex2.position.x - triangle.vertex3.position.x;
    int A31 = triangle.vertex1.position.y - triangle.vertex3.position.y;
    int B31 = triangle.vertex3.position.x - triangle.vertex1.position.x;

    // Loop over the bounding box in steps of 4
    for (int by = min_y; by <= max_y; by += 4) {
        for (int bx = min_x; bx <= max_x; bx += 4) {
            // Compute edge function values at the top-left corner of the block
            int w0 = A23 * (bx - triangle.vertex2.position.x) + B23 * (by - triangle.vertex2.position.y);
            int w1 = A31 * (bx - triangle.vertex3.position.x) + B31 * (by - triangle.vertex3.position.y);
            int w2 = A12 * (bx - triangle.vertex1.position.x) + B12 * (by - triangle.vertex1.position.y);

            // Compute edge function increments
            int dwdx0 = A23;
            int dwdy0 = B23;
            int dwdx1 = A31;
            int dwdy1 = B31;
            int dwdx2 = A12;
            int dwdy2 = B12;

            // Build masks
            unsigned int mask0 = build_mask_linear(w0, dwdx0, dwdy0);
            unsigned int mask1 = build_mask_linear(w1, dwdx1, dwdy1);
            unsigned int mask2 = build_mask_linear(w2, dwdx2, dwdy2);

            // Combine masks to find pixels inside the triangle
            unsigned int mask = ~(mask0 | mask1 | mask2);
			/* if (mask == 0xffffffff) */
			/* 	do_mask_full_sse(by, bx, mlx, triangle, zbuffer, color); */
			printf("oio");
			if (mask)
				do_mask(mask, by, bx, mlx, triangle, zbuffer, color);
        }
    }
}
