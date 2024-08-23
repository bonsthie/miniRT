/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gizmo_to_obj.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 20:54:22 by babonnet          #+#    #+#             */
/*   Updated: 2024/08/23 14:44:18 by bonsthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "object.h"
#include "rt_mesh_obj.h"
#include "rt_scene_elements.h"

void	translate_gizmo_to_obj(t_scene *scene, t_object_mesh *gizmo)
{
	t_object		*object;
	t_object_mesh	*obj_mesh;
	t_status		*status;

	status = &scene->status;
	object = get_obj_by_id(scene->object, status->object_selected_id);
	if (!object)
		return ;
	obj_mesh = object->object;
	gizmo->new_offset.x = obj_mesh->center.vec3.x - gizmo->center.vec3.x;
	gizmo->new_offset.y = obj_mesh->center.vec3.y - gizmo->center.vec3.y;
	gizmo->new_offset.z = obj_mesh->center.vec3.z - gizmo->center.vec3.z;
	gizmo->new_rotation.yaw = obj_mesh->rotation.yaw - gizmo->rotation.yaw;
	gizmo->new_rotation.pitch = obj_mesh->rotation.pitch
		- gizmo->rotation.pitch;
	gizmo->new_rotation.roll = obj_mesh->rotation.roll - gizmo->rotation.roll;
	update_size_obj(gizmo, ALL);
	find_center(gizmo, gizmo->mesh.vertex_init, &gizmo->center.v4f);
}

void	update_gizmo_position(t_scene *scene)
{
	t_object_mesh	*gizmo;
	t_asset			*asset;
	t_status		*status;

	asset = &scene->asset;
	status = &scene->status;
	if (status->gizmo_selected == GIZMO_TRANSLATE)
		gizmo = asset->gizmo_translate;
	else if (status->gizmo_selected == GIZMO_SCALE)
		gizmo = asset->gizmo_scale;
	else
		return ;
	translate_gizmo_to_obj(scene, gizmo);
	rt_set_image_color(asset->gizmo_img, 0);
	print_obj_to_image(gizmo, asset->gizmo_img, 1);
}
