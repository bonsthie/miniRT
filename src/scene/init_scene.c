/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 15:07:19 by babonnet          #+#    #+#             */
/*   Updated: 2024/07/22 20:46:29 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_driver.h"
#include "object.h"
#include "rt_mesh_obj.h"
#include "rt_scene_elements.h"
#include <stdio.h>

int init_asset(t_asset *asset)
{
	asset->gizmo_img = malloc(sizeof(t_img));
	if (!asset->gizmo_img)
		return (1);
	rt_set_image_color(asset->gizmo_img, 0);
	asset->gizmo_translate = parse_rta("asset/translate_arrow.rta", NULL);
	if (!asset->gizmo_translate)
		return (1);	
	update_size_obj(asset->gizmo_translate, ALL);
	down_center(asset->gizmo_translate);
	return(0);
}

int scene_init(t_scene *scene)
{
	if (init_asset(&scene->asset))
	{
		if (scene->asset.gizmo_img)
			free(scene->asset.gizmo_img);
		return (1);
	}
	scene->object = NULL;
	scene->cam.coord_axes = (t_v4f){0, 0, 0, 0};
	scene->cam.coord_translation = (t_v4f){0, 0, 0, 0};
	scene->cam.rotation = (t_rotation){0, 0, 0};
	scene->cam.zoom = 100;
	scene->cam.move_usage = NO_MOVE;
	return (0);
}
