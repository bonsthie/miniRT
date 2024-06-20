/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_scene.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yroussea <yroussea@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 13:14:19 by yroussea          #+#    #+#             */
/*   Updated: 2024/06/20 13:39:29 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_driver.h"
#include "rt_mesh_obj.h"
#include <rt_math.h>

t_v4f get_screen_center(void)
{
    return ((t_v4f){RT_WIDTH / 2.0f, RT_HEIGHT / 2.0f, 100.0f, 1.0f});
}

void	create_rotation_tr_matrix(t_v4f *tr, t_rotation rotate)
{
	rotate_yaw(rotate, tr);
	rotate_pitch(rotate, tr);
	rotate_roll(rotate, tr);
}

void	rotate_center(t_v4f *tr, t_v4f *vertex)
{
	t_v4f tmp = *vertex - get_screen_center();
	matrix_multiplication1x4(tr, tmp, &tmp);
	*vertex = tmp + get_screen_center();
}

void	test_center(t_v4f *tr, t_offset *off)
{
	t_v4f tmp = (t_v4f){off->x, off->y, off->z, 0} - get_screen_center();
	matrix_multiplication1x4(tr, tmp, &tmp);
	tmp += get_screen_center();
	*off = (t_offset){tmp[0], tmp[1], tmp[2]};
}

void	update_single_object(t_object_mesh *object, t_v4f *tr)
{
	#pragma omp parallel for
	for (size_t i = 0; i < object->mesh.size_mesh.vertex; i++)
	{
		rotate_center(tr, &object->mesh.vertex[i].v4f);
	}
	// rotate_center(tr, (t_v4f *)&object->offset.x);
	test_center(tr, &object->offset);
}

void	update_scene(t_object_mesh *object)
{
	static t_rotation	lambda = (t_rotation){0, 1, 0};
	t_v4f				tr[4];

	tr[0] = (t_v4f){1, 0, 0, 0};
	tr[1] = (t_v4f){0, 1, 0, 0};
	tr[2] = (t_v4f){0, 0, 1, 0};
	tr[3] = (t_v4f){0, 0, 0, 1};
	create_rotation_tr_matrix(tr, lambda);
	update_single_object(object, tr);
}
