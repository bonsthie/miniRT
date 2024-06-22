/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 15:07:19 by babonnet          #+#    #+#             */
/*   Updated: 2024/06/22 18:38:30 by babonnet         ###   ########.fr       */
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
	scene->cam.coord = (t_v4f){(float)RT_WIDTH / 2, (float)RT_HEIGHT / 2, -100, 0};
	return (0);
}
