/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 17:57:08 by babonnet          #+#    #+#             */
/*   Updated: 2024/06/05 01:09:53 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../_rt_mlx.h"
#include <mlx.h>
#include <stdlib.h>

int init_mlx_data(t_mlx *mlx)
{
	mlx->screen.connection = mlx_init();
	if (!mlx->screen.connection)
		return (1);
	mlx->screen.window = mlx_new_window(mlx->screen.connection, WIDTH, HEIGHT, "miniRT");
	if (!mlx->screen.window)
	{
		free(mlx->screen.connection);
		return (1);
	}
	return (0);
}
