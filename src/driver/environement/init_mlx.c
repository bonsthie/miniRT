/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 17:57:08 by babonnet          #+#    #+#             */
/*   Updated: 2024/06/03 18:00:36 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_rt_mlx.h"
#include <mlx.h>
#include <stdlib.h>

int init_mlx_data(t_mlx *mlx)
{
	mlx->connection = mlx_init();
	if (!mlx->connection)
		return (1);
	mlx->window = mlx_new_window(mlx->connection, WIDTH, HEIGHT, "miniRT");
	if (!mlx->window)
	{
		free(mlx->connection);
		return (1);
	}
	return (0);
}
