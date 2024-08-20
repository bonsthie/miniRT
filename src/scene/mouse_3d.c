/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_3d.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 00:29:52 by babonnet          #+#    #+#             */
/*   Updated: 2024/08/19 16:24:35 by bonsthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "object.h"
#include "rt_driver.h"
#include "rt_scene_elements.h"
#include <stdio.h>

union u_vec	get_mouse_pos_3d(t_screen *screen)
{
	union u_vec	mouse;
	int			x;
	int			y;

	rt_mouse_get_pos(screen, &x, &y);
	mouse.vec3.x = x;
	mouse.vec3.y = y;
	mouse.vec3.z = 1.0f;
	return (mouse);
}

void	update_mouse_3d_pos(union u_vec *mouse_3d, t_v4f tr[4])
{
	rotate_center(tr, mouse_3d->v4f, &mouse_3d->v4f);
}

union u_vec	mouse_pose_relative_to_object(union u_vec mouse_3d,
		t_object *object)
{
	t_object_mesh	*mesh;
	t_object_mesh	dummy;
	t_v4f			transformation[4];

	mesh = object->object;
	dummy.new_scale = mesh->scale;
	dummy.new_offset = mesh->offset;
	dummy.new_rotation = mesh->rotation;
	create_transformation_matrix(transformation, &dummy, ALL);
	rotate(transformation, &mouse_3d.v4f, mesh->center.v4f);
	return (mouse_3d);
}
