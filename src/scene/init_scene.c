/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 15:07:19 by babonnet          #+#    #+#             */
/*   Updated: 2024/06/22 20:12:55 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_driver.h"
#include "rt_scene_elements.h"

int init_asset(t_asset *asset)
{
	rt_set_image_color(asset->gizmo_img, 0);
	return(0);
}

int scene_init(t_scene *scene)
{
	scene->object = NULL;
	scene->cam.coord_axes = (t_v4f){0, 0, 0, 0};
	scene->cam.coord_translation = (t_v4f){0, 0, 0, 0};
	scene->cam.rotation = (t_rotation){0, 0, 0};
	scene->cam.zoom = 100;
	scene->cam.move_usage = NO_MOVE;
	return (0);
}
