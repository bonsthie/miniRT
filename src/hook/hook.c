/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 15:05:05 by babonnet          #+#    #+#             */
/*   Updated: 2024/03/22 15:49:37 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hook_int.h"
#include "mlx.h"
#include "mlx_data.h"

void	hook(t_mlx *mlx)
{
	mlx_on_event(mlx->connection, mlx->window, MLX_WINDOW_EVENT, window_hook,
		mlx->connection);
	// mlx_on_event(mlx->connection, mlx->window, MLX_KEYDOWN, keyup_hook,
	// NULL);
	// mlx_on_event(mlx->connection, mlx->window, MLX_MOUSEDOWN, mousedown_hook,
	//	NULL);
	// mlx_on_event(mlx->connection, mlx->window, MLX_MOUSEUP, mouseup_hook,
	//NULL);
	// mlx_on_event(mlx->connection, mlx->window, MLX_MOUSEWHEEL,
	//	mousewheel_hook,
	//	NULL);
}
