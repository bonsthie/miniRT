/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_print_mesh.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 14:55:43 by babonnet          #+#    #+#             */
/*   Updated: 2024/06/21 15:24:19 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_rt_rasterizer.h"

void	rt_display_quad_mesh(t_rt_render_info info[4], t_img *img,
		unsigned int color)
{
	plot_line(info[0].vector, info[1].vector, img, color);
	plot_line(info[0].vector, info[2].vector, img, color);
	plot_line(info[1].vector, info[2].vector, img, color);
	plot_line(info[2].vector, info[3].vector, img, color);
	plot_line(info[0].vector, info[3].vector, img, color);
}

void	rt_display_triangle_mesh(t_rt_render_info info[3], t_img *img,
		unsigned int color)
{
	plot_line(info[0].vector, info[1].vector, img, color);
	plot_line(info[0].vector, info[2].vector, img, color);
	plot_line(info[1].vector, info[2].vector, img, color);
}
