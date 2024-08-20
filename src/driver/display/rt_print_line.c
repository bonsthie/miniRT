/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_print_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 11:31:21 by babonnet          #+#    #+#             */
/*   Updated: 2024/08/19 16:24:35 by bonsthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../_rt_mlx.h"
#include "_rt_rasterizer.h"
#include <math.h>
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

void	plot_line(t_vec3 v1, t_vec3 v2, t_img *img, unsigned int color)
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
		if (x.first_point < RT_WIDTH && y.first_point < RT_HEIGHT
			&& x.first_point >= 0 && y.first_point >= 0)
		{
			img->color[y.first_point][x.first_point] = color;
		}
		if (x.first_point == x.second_point && y.first_point == y.second_point)
			break ;
		update_position(&x, &y, &err);
	}
}

void	rt_display_line(t_rt_render_info *info, t_img *img, unsigned int color)
{
	plot_line(info->vertex[0].vec3, info->vertex[1].vec3, img, color);
}
