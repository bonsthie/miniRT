/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 16:56:18 by babonnet          #+#    #+#             */
/*   Updated: 2024/06/20 14:37:03 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt_driver.h>
#include <rt_mesh_obj.h>
#include "_rasterizer.h"

void	display_quad_mesh(t_rt_render_info info[4], t_img *img, unsigned int color)
{
	plot_line(info[0].vector, info[1].vector, img, color);
	plot_line(info[0].vector, info[2].vector, img, color);
	plot_line(info[1].vector, info[2].vector, img, color);
	plot_line(info[2].vector, info[3].vector, img, color);
	plot_line(info[0].vector, info[3].vector, img, color);
}

void	display_triangle_mesh(t_rt_render_info info[3], t_img *img, unsigned int color)
{
	plot_line(info[0].vector, info[1].vector, img, color);
	plot_line(info[0].vector, info[2].vector, img, color);
	plot_line(info[1].vector, info[2].vector, img, color);
}

void	display_quad_rast(t_rt_render_info info[4], t_img *img, unsigned int color, int id)
{
	t_tri	triangle;

	triangle.vertex1.position = info[0].vector;
	triangle.vertex2.position = info[1].vector;
	triangle.vertex3.position = info[2].vector;
	triangle.id = id;
	rast_tri(triangle, img, color);                               
	triangle.vertex3.position = info[3].vector;
	triangle.vertex2.position = info[2].vector;
	rast_tri(triangle, img, color);
}

void	display_triangle_rast(t_rt_render_info info[3], t_img *img, unsigned int color, int id)
{
	t_tri	triangle;

	triangle.vertex1.position = info[0].vector;
	triangle.vertex2.position = info[1].vector;
	triangle.vertex3.position = info[2].vector;
	triangle.id = id;
	rast_tri(triangle, img, color);
}

void	display_line(t_rt_render_info info[2], t_img *img, unsigned int color)
{
	plot_line(info[0].vector, info[1].vector, img, color);
}

/* void	display_point(t_point *point, t_mesh mesh, t_img *img, unsigned int color) */
/* { */
/* 	img->color[] */
/* } */
