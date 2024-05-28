/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uptdate_size_obj.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 22:04:37 by babonnet          #+#    #+#             */
/*   Updated: 2024/05/28 20:34:07 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "math.h"
#include "maths.h"
#include "mesh_obj.h"
#include "miniRT.h"

#include <stdio.h>

void create_transformation_matrix(t_v4f *transformation, t_object_mesh *object)
{
	t_v4f matrix_pitch[4];
	t_v4f matrix_yaw[4];
	t_v4f matrix_scale[4];
	t_v4f temp_matrix[4];
	t_rotation rotation = object->new_rotation;

	rotation.pitch *= (M_PI / 180.0);
	rotation.yaw *= (M_PI / 180.0);
	
	t_rotation_metrics metrics;
	metrics.cos_pitch = cos(rotation.pitch);
	metrics.sin_pitch = sin(rotation.pitch);
	metrics.cos_yaw = cos(rotation.yaw);
	metrics.sin_yaw = sin(rotation.yaw);

	matrix_pitch[0] = (t_v4f){1, 0, 0, 0};
	matrix_pitch[1] = (t_v4f){0, metrics.cos_pitch, -metrics.sin_pitch, 0};
	matrix_pitch[2] = (t_v4f){0, metrics.sin_pitch, metrics.cos_pitch, 0};
	matrix_pitch[3] = (t_v4f){0, 0, 0, 1};

	matrix_yaw[0] = (t_v4f){metrics.cos_yaw, 0, metrics.sin_yaw, 0};
	matrix_yaw[1] = (t_v4f){0, 1, 0, 0};
	matrix_yaw[2] = (t_v4f){-metrics.sin_yaw, 0, metrics.cos_yaw, 0};
	matrix_yaw[3] = (t_v4f){0, 0, 0, 1};

	matrix_scale[0] = (t_v4f){object->new_scale, 0, 0, 0};
	matrix_scale[1] = (t_v4f){0, object->new_scale, 0, 0};
	matrix_scale[2] = (t_v4f){0, 0, object->new_scale, 0};
	matrix_scale[3] = (t_v4f){0, 0, 0, 1};

	matrix_multiplication4x4(temp_matrix, matrix_pitch, matrix_yaw);
	matrix_multiplication4x4(transformation, temp_matrix, matrix_scale);

	transformation[0][3] += -object->center.vec3.x;
	transformation[1][3] += -object->center.vec3.y;
	transformation[2][3] += -object->center.vec3.z;
}

void reset_transformation(t_object_mesh *object)
{
	object->scale += object->new_scale;
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


void find_center(t_object_mesh *object)
{
	size_t i;
	size_t size;

	i = 0;
	object->center.v4f = (t_v4f){0, 0, 0, 0};
	size = object->mesh.size_mesh.vertex;
	while (i < size)
	{
		object->center.v4f += object->mesh.vertex[i].v4f;
		i++;
	}
	object->center.v4f /= (t_v4f){size, size, size, 1};
	object->center.vec3.x -= object->offset.x;
	object->center.vec3.y -= object->offset.y;
	object->center.vec3.z -= object->offset.z;
}


void update_size_obj(t_object_mesh *object)
{
	t_v4f transforamtion[4];
	size_t i;

	find_center(object);
	create_transformation_matrix(transforamtion, object);
	i = 0;
	while(i < object->mesh.size_mesh.vertex)
	{
		matrix_multiplication1x4(transforamtion, object->mesh.vertex[i].v4f, &object->mesh.vertex[i].v4f);
		i++;
	}
	i = 0;
	while(i < object->mesh.size_mesh.normal)
	{
		matrix_multiplication1x4(transforamtion, object->mesh.normal[i].v4f, &object->mesh.normal[i].v4f);
		i++;
	}
	reset_transformation(object);
}
