/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_print_mesh.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 14:55:43 by babonnet          #+#    #+#             */
/*   Updated: 2024/06/22 18:33:44 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_rt_rasterizer.h"

void	rt_display_quad_mesh(t_rt_render_info *info, t_img *img,
		unsigned int color)
{
	plot_line(info->vertex[0].vec3, info->vertex[1].vec3, img, color);
	plot_line(info->vertex[0].vec3, info->vertex[2].vec3, img, color);
	plot_line(info->vertex[1].vec3, info->vertex[2].vec3, img, color);
	plot_line(info->vertex[2].vec3, info->vertex[3].vec3, img, color);
	plot_line(info->vertex[0].vec3, info->vertex[3].vec3, img, color);
}

void	rt_display_triangle_mesh(t_rt_render_info *info, t_img *img,
		unsigned int color)
{
	plot_line(info->vertex[0].vec3, info->vertex[1].vec3, img, color);
	plot_line(info->vertex[0].vec3, info->vertex[2].vec3, img, color);
	plot_line(info->vertex[1].vec3, info->vertex[2].vec3, img, color);
}
