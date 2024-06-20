/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_math.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 22:09:47 by babonnet          #+#    #+#             */
/*   Updated: 2024/06/20 13:25:37 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATHS_H
# define MATHS_H

#include <rt_driver.h>
#include <rt_mesh_obj.h>

typedef struct s_position_matrix
{
	t_v4f	*pitch;
	t_v4f	*yaw;
	t_v4f	*scale;
}			t_position_matrix;

typedef struct s_rotation_metrics
{
	double	cos;
	double	sin;
}			t_rotation_metrics;

void		matrix_multiplication4x4(t_v4f result[4], t_v4f a[4],
				t_v4f b[4]);
void		matrix_multiplication1x4(t_v4f *matrix, t_v4f vector,
				t_v4f *result);

void		rotate_yaw(t_rotation rotate, t_v4f *tr);
void		rotate_pitch(t_rotation rotate, t_v4f *tr);
void		rotate_roll(t_rotation rotate, t_v4f *tr);

#endif
