/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 11:31:21 by babonnet          #+#    #+#             */
/*   Updated: 2024/03/21 11:34:17 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "print_int.h"
//
//static inline void	update_position(t_line_param *x, t_line_param *y, int *err)
//{
//	int	e2;
//
//	e2 = 2 * *err;
//	if (e2 >= y->d)
//	{
//		*err += y->d;
//		x->first_point += x->s;
//	}
//	if (e2 <= x->d)
//	{
//		*err += x->d;
//		y->first_point += y->s;
//	}
//}
//
//static inline int	init_s(int x, int y)
//{
//	int	s;
//
//	s = -1;
//	if (x < y)
//		s = 1;
//	return (s);
//}
//
//void	plot_line(t_data *mlx, int *v1, int *v2, int color)
//{
//	t_line_param	x;
//	t_line_param	y;
//	int				err;
//
//	x.first_point = v1[0];
//	y.first_point = v1[1];
//	x.second_point = v2[0];
//	y.second_point = v2[1];
//	x.s = init_s(x.first_point, x.second_point);
//	y.s = init_s(y.first_point, y.second_point);
//	x.d = abs(x.second_point - x.first_point);
//	y.d = -abs(y.second_point - y.first_point);
//	err = x.d + y.d;
//	while (1)
//	{
//		if (x.first_point < WIDTH && y.first_point < HEIGHT
//			&& x.first_point >= 0 && y.first_point >= 0)
//			mlx_set_image_pixel(mlx->connection, mlx->image, x.first_point,
//				y.first_point, color);
//		if (x.first_point == x.second_point && y.first_point == y.second_point)
//			break ;
//		update_position(&x, &y, &err);
//	}
//}
