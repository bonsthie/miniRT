/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_print_rast.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 16:56:18 by babonnet          #+#    #+#             */
/*   Updated: 2024/06/21 15:24:19 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_rt_rasterizer.h"
#include <rt_driver.h>
#include <rt_mesh_obj.h>

void	rt_display_quad_rast(t_rt_render_info info[4], t_img *img,
		unsigned int color, int id)
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

void	rt_display_triangle_rast(t_rt_render_info info[3], t_img *img,
		unsigned int color, int id)
{
	t_tri	triangle;

	triangle.vertex1.position = info[0].vector;
	triangle.vertex2.position = info[1].vector;
	triangle.vertex3.position = info[2].vector;
	triangle.id = id;
	rast_tri(triangle, img, color);
}
