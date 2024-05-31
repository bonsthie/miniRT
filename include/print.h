/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 21:34:06 by babonnet          #+#    #+#             */
/*   Updated: 2024/05/31 20:45:11 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINT_H
#define PRINT_H


#include "mesh_obj.h"
#include "mlx_data.h"

void print_obj(t_object_mesh *object, t_mlx *mlx, int zbuffer[HEIGHT][WIDTH]);

#endif
