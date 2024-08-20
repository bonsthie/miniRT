/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gizmo_move_object.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 18:14:49 by babonnet          #+#    #+#             */
/*   Updated: 2024/07/27 17:10:30 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "object.h"
#include "rt_scene_elements.h"
#include "rt_mesh_obj.h"
#include <stdio.h>

void gizmo_move_object(t_scene *scene)
{
	t_object *obj;
	t_object_mesh *mesh_obj;
	t_status	*status;

	status = &scene->status;
	obj = get_obj_by_id(scene->object, status->object_selected_id);
	if (!obj)
		return ;
	mesh_obj = obj->object;
	if (status->gizmo_axe_selected == GIZMO_AXE_Y)
		mesh_obj->new_offset.x = scene->mouse_3d.vec3.x - scene->prev_mouse_3d.vec3.x;
	else if (status->gizmo_axe_selected == GIZMO_AXE_X)
		mesh_obj->new_offset.z = -(scene->mouse_3d.vec3.z - scene->prev_mouse_3d.vec3.z);
	else if (status->gizmo_axe_selected == GIZMO_AXE_Z)
		mesh_obj->new_offset.y = scene->mouse_3d.vec3.y - scene->prev_mouse_3d.vec3.y;
	else
		return ;
	update_size_obj(mesh_obj, TRANSLATE);
}
