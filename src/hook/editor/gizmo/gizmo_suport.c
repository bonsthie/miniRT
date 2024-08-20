/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gizmo_suport.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 15:37:59 by babonnet          #+#    #+#             */
/*   Updated: 2024/07/23 16:33:15 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "object.h"
#include "rt_driver.h"

#define RED 0xFFFF0000
#define GREEN 0xFF00FF00
#define BLUE 0xFF0000FF

int gizmo_support(t_scene *scene, t_screen *screen)
{
	t_asset *asset;
	t_status *status;
	unsigned int color;

	status = &scene->status;
	if (!status->gizmo_selected && !status->object_selected_id)
		return (1);
	asset = &scene->asset;
	rt_set_image_color(asset->gizmo_img, 0);
	print_obj_to_image(asset->gizmo_translate, scene->asset.gizmo_img, 1);
	rt_print_img_screen(asset->gizmo_img, screen, 0, 0);
	color = rt_get_color_under_cursor(screen, asset->gizmo_img);
	if (!color)
		return (1);
	/* else if (color == RED) */
	/* 	translate_x */
		
	return (0);
}
