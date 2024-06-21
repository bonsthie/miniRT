/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_rast_tri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 15:29:06 by babonnet          #+#    #+#             */
/*   Updated: 2024/06/21 17:52:35 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../_rt_mlx.h"
#include "_rt_rasterizer.h"
#include <math.h>
#include <rt_driver.h>

#if defined(__AVX2__)
# include <immintrin.h>

static inline unsigned	build_mask_linear(int c, int dcdx, int dcdy)
{
	__m128i	cstep0;
	__m128i	xdcdy;
	__m128i	cstep1;
	__m128i	cstep2;
	__m128i	cstep3;
	__m128i	cstep01;
	__m128i	cstep23;
	__m128i	result;

	cstep0 = _mm_setr_epi32(c, c + dcdx, c + dcdx * 2, c + dcdx * 3);
	xdcdy = _mm_set1_epi32(dcdy);
	/* Get values across the quad
		*/
	cstep1 = _mm_add_epi32(cstep0, xdcdy);
	cstep2 = _mm_add_epi32(cstep1, xdcdy);
	cstep3 = _mm_add_epi32(cstep2, xdcdy);
	/* pack pairs of results into epi16
		*/
	cstep01 = _mm_packs_epi32(cstep0, cstep1);
	cstep23 = _mm_packs_epi32(cstep2, cstep3);
	/* pack into epi8, preserving sign bits
		*/
	result = _mm_packs_epi16(cstep01, cstep23);
	/* extract sign bits to create mask
		*/
	return (_mm_movemask_epi8(result));
}

#else

unsigned	build_mask_linear(int32_t c, int32_t dcdx, int32_t dcdy)
{
	unsigned int	mask;
	int32_t			c0;
	int32_t			c1;
	int32_t			c2;
	int32_t			c3;

	c0 = c;
	c1 = c0 + dcdy;
	c2 = c1 + dcdy;
	c3 = c2 + dcdy;
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
	return (mask);
}
#endif

void	do_mask(int mask, int by, int bx, t_tri triangle, t_img *img,
		unsigned int color)
{
	unsigned int	endy;
	unsigned int	endx;

	endy = by + 4;
	endx = bx + 4;
	for (unsigned int y = by; y < endy; y++)
	{
		for (unsigned int x = bx; x < endx; x++)
		{
			if (mask & 1)
			{
				if (triangle.vertex1.position.z <= img->zbuffer[y][x])
				{
					img->zbuffer[y][x] = triangle.vertex1.position.z;
					img->color[y][x] = color;
					img->obj_id[y][x] = triangle.id;
				}
			}
			mask >>= 1;
		}
	}
}

typedef struct s_bbox
{
	int					min_x;
	int					min_y;
	int					max_x;
	int					max_y;
}						t_bbox;

typedef union u_edge_coef
{
	__m256i				avx_edge;
	struct
	{
		int				dwdx2;
		int				dwdy2;
		int				dwdx0;
		int				dwdy0;
		int				dwdx1;
		int				dwdy1;
	};
}						t_edge_coef;

t_bbox	calcul_bbox_triangle(t_tri triangle)
{
	t_bbox	bbox;

	bbox.min_x = (int)fmin(triangle.vertex1.position.x,
			fmin(triangle.vertex2.position.x, triangle.vertex3.position.x));
	bbox.min_y = (int)fmin(triangle.vertex1.position.y,
			fmin(triangle.vertex2.position.y, triangle.vertex3.position.y));
	bbox.max_x = (int)fmax(triangle.vertex1.position.x,
			fmax(triangle.vertex2.position.x, triangle.vertex3.position.x));
	bbox.max_y = (int)fmax(triangle.vertex1.position.y,
			fmax(triangle.vertex2.position.y, triangle.vertex3.position.y));
	bbox.min_x = fmax(bbox.min_x, 0);
	bbox.min_y = fmax(bbox.min_y, 0);
	bbox.max_x = fmin(bbox.max_x, RT_WIDTH - 1);
	bbox.max_y = fmin(bbox.max_y, RT_HEIGHT - 1);
	return (bbox);
}

void	rast_tri(t_tri triangle, t_img *img, unsigned int color)
{
	t_bbox			bbox;
	t_edge_coef		edge_coef;
	int				w0;
	int				w1;
	int				w2;
	unsigned int	mask0;
	unsigned int	mask1;
	unsigned int	mask2;
	unsigned int	mask;

	bbox = calcul_bbox_triangle(triangle);
	// Edge function coefficients
	edge_coef.dwdx2 = (triangle.vertex2.position.y
			- triangle.vertex1.position.y) * (1 << FIXED_ORDER);
	edge_coef.dwdy2 = (triangle.vertex1.position.x
			- triangle.vertex2.position.x) * (1 << FIXED_ORDER);
	edge_coef.dwdx0 = (triangle.vertex3.position.y
			- triangle.vertex2.position.y) * (1 << FIXED_ORDER);
	edge_coef.dwdy0 = (triangle.vertex2.position.x
			- triangle.vertex3.position.x) * (1 << FIXED_ORDER);
	edge_coef.dwdx1 = (triangle.vertex1.position.y
			- triangle.vertex3.position.y) * (1 << FIXED_ORDER);
	edge_coef.dwdy1 = (triangle.vertex3.position.x
			- triangle.vertex1.position.x) * (1 << FIXED_ORDER);
	// Loop over the bounding box in steps of 4
	for (int by = bbox.min_y; by <= bbox.max_y; by += 4)
	{
		for (int bx = bbox.min_x; bx <= bbox.max_x; bx += 4)
		{
			// Compute edge function values at the top-left corner of the block
			w0 = edge_coef.dwdx0 * (bx - triangle.vertex2.position.x)
				+ edge_coef.dwdy0 * (by - triangle.vertex2.position.y);
			w1 = edge_coef.dwdx1 * (bx - triangle.vertex3.position.x)
				+ edge_coef.dwdy1 * (by - triangle.vertex3.position.y);
			w2 = edge_coef.dwdx2 * (bx - triangle.vertex1.position.x)
				+ edge_coef.dwdy2 * (by - triangle.vertex1.position.y);
			// Build masks
			mask0 = build_mask_linear(w0, edge_coef.dwdx0, edge_coef.dwdy0);
			mask1 = build_mask_linear(w1, edge_coef.dwdx1, edge_coef.dwdy1);
			mask2 = build_mask_linear(w2, edge_coef.dwdx2, edge_coef.dwdy2);
			// Combine masks to find pixels inside the triangle
			mask = ~(mask0 | mask1 | mask2);
			if (mask)
				do_mask(mask, by, bx, triangle, img, color);
		}
	}
}
