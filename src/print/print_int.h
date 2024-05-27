/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_int.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 11:32:42 by babonnet          #+#    #+#             */
/*   Updated: 2024/05/27 16:05:28 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINT_INT_H
#define PRINT_INT_H

#include "mesh_obj.h"
#include "miniRT.h"
#include "mlx_data.h"

typedef struct s_line_parm
{
	int	first_point;
	int	second_point;
	int	d;
	int	s;
}		t_line_param;

void	plot_line(t_mlx *mlx, t_v4f v1, t_v4f v2, int color);
void rast_tri(t_point *point, t_mesh mesh, t_mlx *mlx);

#endif
