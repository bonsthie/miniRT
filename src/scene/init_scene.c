/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 15:07:19 by babonnet          #+#    #+#             */
/*   Updated: 2024/08/23 17:20:05 by bonsthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "object.h"
#include "rt_driver.h"
#include "rt_mesh_obj.h"
#include "rt_scene_elements.h"
#include <stdio.h>

int	init_asset(t_asset *asset)
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

	// need to manage if this parsing fail
	asset->gizmo_scale = parse_rta("asset/ScalePivot.rta", NULL);
	if (!asset->gizmo_scale)
		return (1);
	update_size_obj(asset->gizmo_scale, ALL);
	asset->gizmo_rotate = parse_rta("asset/RotatePivot.rta", NULL);
	if (!asset->gizmo_rotate)
		return (1);
	update_size_obj(asset->gizmo_rotate, ALL);
	down_center(asset->gizmo_scale);

	return (0);
}

int	scene_init(t_scene *scene)
{
	if (init_asset(&scene->asset))
	{
		if (scene->asset.gizmo_img)
			free(scene->asset.gizmo_img);
		return (1);
	}
	ft_bzero(&scene->status, sizeof(t_status));
	ft_bzero(&scene->cam, sizeof(t_camera));
	scene->object = NULL;
	scene->cam.zoom = 100;
	scene->cam.move_usage = NO_MOVE;
	return (0);
}
