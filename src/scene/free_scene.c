/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bonsthie <bonsthie@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 14:13:03 by bonsthie          #+#    #+#             */
/*   Updated: 2024/08/29 14:19:18 by bonsthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "rt_scene_elements.h"
#include "rt_mesh_obj.h"

void free_scene_asset(t_asset *asset)
{
	if (!asset)
		return ;
	if (asset->gizmo_img)
		free(asset->gizmo_img);
	/* if (asset->gizmo_scale) */
	/* 	free_ob(asset->gizmo_scale); */

}
