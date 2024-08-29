/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_scene.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 13:14:19 by yroussea          #+#    #+#             */
/*   Updated: 2024/08/29 15:54:54 by bonsthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_driver.h"
#include "rt_mesh_obj.h"
#include <rt_math.h>
#include <rt_scene_elements.h>
#include <stdbool.h>

t_v4f	get_screen_center(void)
{
	return ((t_v4f){RT_WIDTH / 2.0f, RT_HEIGHT / 2.0f, 100.0f, 1.0f});
}

void	create_rotation_tr_matrix(t_v4f *tr, t_rotation rotate, t_v4f offset)
{
	rotate_pitch(rotate, tr);
	rotate_yaw(rotate, tr);
	rotate_roll(rotate, tr);
	tr[0][3] = offset[0];
	tr[1][3] = offset[1];
	tr[2][3] = offset[2];
}

void	rotate_center(t_v4f *tr, t_v4f vertex, t_v4f *result)
{
	t_v4f	tmp;

	tmp = vertex - get_screen_center();
	tmp[3] = 1;
	matrix_multiplication1x4(tr, tmp, &tmp);
	*result = tmp + get_screen_center();
}

void	update_single_object(t_object_mesh *object, t_v4f *tr)
{
	find_center(object, &(object->mesh.vertex->v4f),
		&object->relative_center.v4f);
/* #pragma omp parallel for */
	for (size_t i = 0; i < object->mesh.size_mesh.vertex; i++)
		rotate_center(tr, object->mesh.vertex_init[i],
			&object->mesh.vertex[i].v4f);
	rotate_center(tr, object->saving_point.v4f, &object->relative_point.v4f);
}

#include <stdio.h>

void	update_scene(t_scene *scene)
{
	t_v4f		tr[4];
	t_object	*object;
	t_camera	*cam;

	object = scene->object;
	cam = &scene->cam;
	tr[0] = (t_v4f){cam->zoom / 100, 0, 0, 0};
	tr[1] = (t_v4f){0, cam->zoom / 100, 0, 0};
	tr[2] = (t_v4f){0, 0, cam->zoom / 100, 0};
	tr[3] = (t_v4f){0, 0, 0, 1};
	create_rotation_tr_matrix(tr, cam->rotation, cam->coord_translation);
	while (object)
	{
		update_single_object(object->object, tr);
		object = object->next;
	}
	update_single_object(scene->asset.gizmo_translate, tr);
	update_single_object(scene->asset.gizmo_scale, tr);
	update_single_object(scene->asset.gizmo_rotate, tr);
	update_mouse_3d_pos(&scene->mouse_3d, tr);
}
