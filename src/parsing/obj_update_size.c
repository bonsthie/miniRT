/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_update_size.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 22:04:37 by babonnet          #+#    #+#             */
/*   Updated: 2024/07/21 18:21:21 by yroussea         ###   ########.fr       */
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
	// if (settings & ROT_CENTER_OBJ)
	// {
	// 	transformation[0][3] -= object->center.vec3.x;
	// 	transformation[1][3] -= object->center.vec3.y;
	// 	transformation[2][3] -= object->center.vec3.z;
	// }
	transformation[0][3] = object->new_offset.x;
	transformation[1][3] = object->new_offset.y;
	transformation[2][3] = object->new_offset.z;
}

__always_inline
void	rotate(t_v4f *tr, t_v4f *result, t_v4f center)
{
	t_v4f tmp = *result - center;
	tmp[3] = 1;
	matrix_multiplication1x4(tr, tmp, &tmp);
	*result = tmp + center;
}

#include <stdio.h>
void	update_size_obj(t_object_mesh *object, uint8_t settings)
{
	t_v4f	transforamtion[4];

	transforamtion[0] = (t_v4f){1, 0, 0, 0};
	transforamtion[1] = (t_v4f){0, 1, 0, 0};
	transforamtion[2] = (t_v4f){0, 0, 1, 0};
	transforamtion[3] = (t_v4f){0, 0, 0, 1};
	find_center(object, object->mesh.vertex_init, &object->center.v4f);
	// printf("%f %f %f\n",
	// 	object->center.v4f[0],
	// 	object->center.v4f[1],
	// 	object->center.v4f[2]
	// 	);
	create_transformation_matrix(transforamtion, object, settings);
	// matrix_multiplication1x4(transforamtion, object->center.v4f, &object->center.v4f);
	#pragma omp parallel for
	for (size_t i = 0; i < object->mesh.size_mesh.vertex; i++)
		rotate(transforamtion, &object->mesh.vertex_init[i], object->center.v4f);
	if (settings & CENTER)
		for (size_t i = 0; i < object->mesh.size_mesh.vertex; i++)
			object->mesh.vertex_init[i] += (t_v4f){(float)RT_WIDTH / 2,
				(float)RT_HEIGHT / 2, 100, 0} - object->center.v4f ;
	reset_transformation(object);
}
