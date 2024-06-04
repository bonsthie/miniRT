/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rast_tri.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 15:29:06 by babonnet          #+#    #+#             */
/*   Updated: 2024/06/05 00:22:38 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <rt_driver.h>
#include "_rasterizer.h"
#include "../_rt_mlx.h"

#define FIXED_ORDER 11

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

    return mask;
}
#endif

void do_mask(int mask, int by, int bx, t_tri triangle, t_img *img, unsigned int color)
{
	int endy = by  + 4;
	int endx = bx  + 4;
	for (int y = by; y < endy; y++)
	{
		for (int x = bx; x < endx; x++)
		{
			if (mask & 1)
			{
				if (y > 0 && x > 0 && x <= WIDTH && y <= HEIGHT && triangle.vertex1.position.z <= img->zbuffer[y][x])
				{
					img->zbuffer[y][x] = triangle.vertex1.position.z;
					img->color[y][x] = color;
				}
			}
			mask >>= 1;
		}
	}
}

void rast_tri(t_tri triangle, t_img *img, unsigned int color) 
{

    // Bounding box
    int min_x = (int)fmin(triangle.vertex1.position.x, fmin(triangle.vertex2.position.x, triangle.vertex3.position.x));
    int min_y = (int)fmin(triangle.vertex1.position.y, fmin(triangle.vertex2.position.y, triangle.vertex3.position.y));
    int max_x = (int)fmax(triangle.vertex1.position.x, fmax(triangle.vertex2.position.x, triangle.vertex3.position.x));
    int max_y = (int)fmax(triangle.vertex1.position.y, fmax(triangle.vertex2.position.y, triangle.vertex3.position.y));

	min_x = fmax(min_x, 0);
	min_y = fmax(min_y, 0);
	max_x = fmin(max_x, WIDTH - 1);
	max_y = fmin(max_y, HEIGHT - 1);

    // Edge function coefficients
    int dwdx2 = (triangle.vertex2.position.y - triangle.vertex1.position.y) * (1 << FIXED_ORDER);
    int dwdy2 = (triangle.vertex1.position.x - triangle.vertex2.position.x) * (1 << FIXED_ORDER);
    int dwdx0 = (triangle.vertex3.position.y - triangle.vertex2.position.y) * (1 << FIXED_ORDER);
    int dwdy0 = (triangle.vertex2.position.x - triangle.vertex3.position.x) * (1 << FIXED_ORDER);
    int dwdx1 = (triangle.vertex1.position.y - triangle.vertex3.position.y) * (1 << FIXED_ORDER);
    int dwdy1 = (triangle.vertex3.position.x - triangle.vertex1.position.x) * (1 << FIXED_ORDER);

    // Loop over the bounding box in steps of 4
    for (int by = min_y; by <= max_y; by += 4) {
        for (int bx = min_x; bx <= max_x; bx += 4) {
            // Compute edge function values at the top-left corner of the block
            int w0 = dwdx0 * (bx - triangle.vertex2.position.x) + dwdy0 * (by - triangle.vertex2.position.y);
            int w1 = dwdx1 * (bx - triangle.vertex3.position.x) + dwdy1 * (by - triangle.vertex3.position.y);
            int w2 = dwdx2 * (bx - triangle.vertex1.position.x) + dwdy2 * (by - triangle.vertex1.position.y);

            // Build masks
            unsigned int mask0 = build_mask_linear(w0, dwdx0, dwdy0);
            unsigned int mask1 = build_mask_linear(w1, dwdx1, dwdy1);
            unsigned int mask2 = build_mask_linear(w2, dwdx2, dwdy2);

            // Combine masks to find pixels inside the triangle
            unsigned int mask = ~(mask0 | mask1 | mask2);
			if (mask)
				do_mask(mask, by, bx, triangle, img, color);
        }
    }
}
