/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   euler_rotate_transformation.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yroussea <yroussea@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 13:23:17 by yroussea          #+#    #+#             */
/*   Updated: 2024/06/21 00:13:50 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <rt_math.h>
#include <rt_mesh_obj.h>

void	rotate_yaw(t_rotation rotate, t_v4f *tr)
{
	t_v4f				matrix_yaw[4];
	t_rotation_metrics	metrics;

	metrics.cos = cos(M_PI*rotate.yaw/180);
	metrics.sin = sin(M_PI*rotate.yaw/180);
	matrix_yaw[0] = (t_v4f){metrics.cos, 0, metrics.sin, 0};
	matrix_yaw[1] = (t_v4f){0, 1, 0, 0};
	matrix_yaw[2] = (t_v4f){-metrics.sin, 0, metrics.cos, 0};
	matrix_yaw[3] = (t_v4f){0, 0, 0, 1};
	matrix_multiplication4x4(tr, tr, matrix_yaw);
}

void	rotate_pitch(t_rotation rotate, t_v4f *tr)
{
	t_v4f				matrix_pitch[4];
	t_rotation_metrics	metrics;

	metrics.cos = cos(M_PI*rotate.pitch/180);
	metrics.sin = sin(M_PI*rotate.pitch/180);
	matrix_pitch[0] = (t_v4f){1, 0, 0, 0};
	matrix_pitch[1] = (t_v4f){0, metrics.cos, -metrics.sin, 0};
	matrix_pitch[2] = (t_v4f){0, metrics.sin, metrics.cos, 0};
	matrix_pitch[3] = (t_v4f){0, 0, 0, 1};
	matrix_multiplication4x4(tr, tr, matrix_pitch);
}

void	rotate_roll(t_rotation rotate, t_v4f *tr)
{
	t_v4f				matrix_roll[4];
	t_rotation_metrics	metrics;

	metrics.cos = cos(M_PI*rotate.roll/180);
	metrics.sin = sin(M_PI*rotate.roll/180);
	matrix_roll[0] = (t_v4f){metrics.cos, -metrics.sin, 0, 0};
	matrix_roll[1] = (t_v4f){metrics.sin, metrics.cos, 0, 0};
	matrix_roll[2] = (t_v4f){0, 0, 1, 0};
	matrix_roll[3] = (t_v4f){0, 0, 0, 1};
	matrix_multiplication4x4(tr, tr, matrix_roll);
}

