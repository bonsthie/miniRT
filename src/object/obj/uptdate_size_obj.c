/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uptdate_size_obj.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 22:04:37 by babonnet          #+#    #+#             */
/*   Updated: 2024/03/22 23:35:54 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "math.h"
#include "maths.h"
#include "mesh_obj.h"


void create_transformation_matrix(t_v4f *transformation, t_object_mesh *object)
{
	t_position_matrix	matrix;
	t_rotation_metrics	metrics;
	t_rotation			rotation;
	t_v4f				temp_matrix[4];
	
	rotation = object->rotation;
	rotation.pitch *= (M_PI / 180.0);
	rotation.yaw *= (M_PI / 180.0);
	metrics.cos_pitch = cos(rotation.pitch);
	metrics.sin_pitch = sin(rotation.pitch);
	metrics.cos_yaw = cos(rotation.yaw);
	metrics.sin_yaw = sin(rotation.yaw);
	matrix.pitch = (t_v4f[4]){
	{1, 0, 0, object->offset.x}, 
	{0, metrics.cos_pitch, -metrics.sin_pitch, object->offset.y},
	{0, metrics.sin_pitch, metrics.cos_pitch, object->offset.z}, 
	{0, 0, 0, 1}};
	matrix.yaw = (t_v4f[4]){
	{metrics.cos_yaw, 0, metrics.sin_yaw, 0}, {0, 1, 0, 0},
	{-metrics.sin_yaw, 0, metrics.cos_yaw, 0}, {0, 0, 0, 1}};
	matrix.scale = (t_v4f[4]){
	{object->scale, 0, 0, -((1) * object->scale * 0.5)},
	{0, object->scale, 0, -object->scale},
	{0, 0, object->scale, -((1) * object->scale * 0.5)},
	{0, 0, 0, 1}};
	matrix_multiplication4x4(temp_matrix, matrix.pitch, matrix.yaw);
	matrix_multiplication4x4(transformation, temp_matrix, matrix.scale);

}

void update_size_obj(t_object_mesh *object)
{
	t_v4f transforamtion[4];
	size_t i;

	create_transformation_matrix(transforamtion, object);
	i = 0;
	while(i < object->mesh.size_mesh.vertex)
	{
		matrix_multiplication1x4(transforamtion, object->mesh.vertex[i], &object->mesh.vertex[i]);
		i++;
	}
	i = 0;
	while(i < object->mesh.size_mesh.normal)
	{
		matrix_multiplication1x4(transforamtion, object->mesh.normal[i], &object->mesh.normal[i]);
		i++;
	}
}
