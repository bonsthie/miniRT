/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_size_obj.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 22:04:37 by babonnet          #+#    #+#             */
/*   Updated: 2024/06/20 14:31:49 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt_driver.h>
#include <rt_math.h>
#include <rt_mesh_obj.h>
#include <stdbool.h>
#include <sys/cdefs.h>

void	transformation_matrix_scale(t_v4f *transformation,
		t_object_mesh *object)
{
	t_v4f	matrix_scale[4];

	matrix_scale[0] = (t_v4f){object->new_scale, 0, 0, 0};
	matrix_scale[1] = (t_v4f){0, object->new_scale, 0, 0};
	matrix_scale[2] = (t_v4f){0, 0, object->new_scale, 0};
	matrix_scale[3] = (t_v4f){0, 0, 0, 1};
	matrix_multiplication4x4(transformation, transformation, matrix_scale);
}

void	reset_transformation(t_object_mesh *object)
{
	object->scale += object->new_scale - 1;
	object->rotation.pitch += object->new_rotation.pitch;
	object->rotation.yaw += object->new_rotation.yaw;
	object->rotation.roll += object->new_rotation.roll;
	object->offset.x += object->new_offset.x;
	object->offset.y += object->new_offset.y;
	object->offset.z += object->new_offset.z;
	object->new_scale = 1;
	object->new_rotation.pitch = 0;
	object->new_rotation.yaw = 0;
	object->new_rotation.roll = 0;
	object->new_offset.x = 0;
	object->new_offset.y = 0;
	object->new_offset.z = 0;
}

void	find_center(t_object_mesh *object)
{
	size_t	i;
	size_t	size;

	i = 0;
	object->center.v4f = (t_v4f){0, 0, 0, 0};
	size = object->mesh.size_mesh.vertex;
	while (i < size)
	{
		object->center.v4f += object->mesh.vertex[i].v4f;
		i++;
	}
	object->center.v4f /= (t_v4f){size, size, size, 1};
	object->center.v4f -= *(t_v4f *)&object->offset.x;
}

void create_transformation_matrix(t_v4f *transformation, t_object_mesh *object, uint8_t settings)
{

	if (settings & ROT_YAW)
		rotate_yaw(object->new_rotation, transformation);
	if (settings & ROT_PITCH)
		rotate_pitch(object->new_rotation, transformation);
	if (settings & ROT_ROLL)
		rotate_roll(object->new_rotation, transformation);
	if (settings & SCALE)
		transformation_matrix_scale(transformation, object);
	if (settings & ROT_CENTER_OBJ)
	{
		transformation[0][3] -= object->center.vec3.x;
		transformation[1][3] -= object->center.vec3.y;
		transformation[2][3] -= object->center.vec3.z;
	}
}

void	update_size_obj(t_object_mesh *object, uint8_t settings)
{
	t_v4f	transforamtion[4];

	transforamtion[0] = (t_v4f){1, 0, 0, 0};
	transforamtion[1] = (t_v4f){0, 1, 0, 0};
	transforamtion[2] = (t_v4f){0, 0, 1, 0};
	transforamtion[3] = (t_v4f){0, 0, 0, 1};
	find_center(object);
	create_transformation_matrix(transforamtion, object, settings);
	#pragma omp parallel for
	for (size_t i = 0; i < object->mesh.size_mesh.vertex; i++)
	{
		matrix_multiplication1x4(transforamtion, object->mesh.vertex[i].v4f,
			&object->mesh.vertex[i].v4f);
	}
	reset_transformation(object);
}
