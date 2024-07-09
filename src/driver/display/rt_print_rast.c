/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_print_rast.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 16:56:18 by babonnet          #+#    #+#             */
/*   Updated: 2024/06/22 18:30:15 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_rt_rasterizer.h"
#include <rt_driver.h>
#include <rt_mesh_obj.h>

void	rt_display_quad_rast(t_rt_render_info *info, t_img *img,
		int id)
{
	t_tri	triangle;

	triangle.vertex1.position = info->vertex[0].vec3;
	triangle.vertex2.position = info->vertex[1].vec3;
	triangle.vertex3.position = info->vertex[2].vec3;
	triangle.id = id;
	rast_tri(triangle, img, info->color.value);
	triangle.vertex3.position = info->vertex[3].vec3;
	triangle.vertex2.position = info->vertex[2].vec3;
	rast_tri(triangle, img, info->color.value);
}

void	rt_display_triangle_rast(t_rt_render_info *info, t_img *img,
		 int id)
{
	t_tri	triangle;

	triangle.vertex1.position = info->vertex[0].vec3;
	triangle.vertex2.position = info->vertex[1].vec3;
	triangle.vertex3.position = info->vertex[2].vec3;
	triangle.id = id;
	rast_tri(triangle, img, info->color.value);
}
