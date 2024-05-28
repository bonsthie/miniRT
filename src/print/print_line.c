/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 11:31:21 by babonnet          #+#    #+#             */
/*   Updated: 2024/05/28 20:40:24 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "print_int.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static inline void	update_position(t_line_param *x, t_line_param *y, int *err)
{
	int	e2;

	e2 = 2 * *err;
	if (e2 >= y->d)
	{
		*err += y->d;
		x->first_point += x->s;
	}
	if (e2 <= x->d)
	{
		*err += x->d;
		y->first_point += y->s;
	}
}

static inline int	init_s(int x, int y)
{
	int	s;

	s = -1;
	if (x < y)
		s = 1;
	return (s);
}

float	calculate_distance(t_vec3 *center, t_vec3 *point)
{
			return sqrt(pow(point->z - center->z, 2));
}

// Function to calculate and return an RGBA color as an unsigned int
unsigned int	rast_get_color(t_vec3 *center, t_vec3 *point)
{
	float			distance;
	unsigned int	color;

	distance = calculate_distance(center, point);
	unsigned char r, g, b, a = 255; // Alpha is fully opaque
	// Calculate gradient: Red to Blue
	float ratio = distance / 960;        // Normalize the distance
	r = (unsigned char)(255 * (1 - ratio)); // Red decreases
	g = 0;                                  // Green is always 0
	b = (unsigned char)(255 * ratio);       // Blue increases
	// Pack RGBA into an unsigned int
	color = (a << 24) | (r << 16) | (g << 8) | b;
	return (color);
}
void	plot_line(t_mlx *mlx, t_vec3 v1, t_vec3 v2, int color, t_vec3 center)
{
	t_line_param	x;
	t_line_param	y;
	int				err;

	x.first_point = v1.x;
	y.first_point = v1.y;
	x.second_point = v2.x;
	y.second_point = v2.y;
	x.s = init_s(x.first_point, x.second_point);
	y.s = init_s(y.first_point, y.second_point);
	x.d = abs(x.second_point - x.first_point);
	y.d = -abs(y.second_point - y.first_point);
	err = x.d + y.d;
	while (1)
	{
		v1.x = x.first_point;
		v1.y = y.first_point;
		if (x.first_point < WIDTH && y.first_point < HEIGHT
			&& x.first_point >= 0 && y.first_point >= 0)
		{
			/* printf("color = %d\n", rast_get_color(center, v1)); */
			/* mlx_pixel_put(mlx->connection, mlx->window, x.first_point, */
			/* 	y.first_point, rast_get_color(&center, &v1)); */
			mlx_pixel_put(mlx->connection, mlx->window, x.first_point,
				y.first_point, color);
		}
		if (x.first_point == x.second_point && y.first_point == y.second_point)
			break ;
		update_position(&x, &y, &err);
	}
	(void)center;
}
