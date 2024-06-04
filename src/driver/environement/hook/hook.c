/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 15:05:05 by babonnet          #+#    #+#             */
/*   Updated: 2024/06/05 01:12:09 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>

#include "_hook.h"
#include "../../_rt_mlx.h"

void	hook(t_mlx *mlx)
{
	mlx_on_event(mlx->screen.connection, mlx->screen.window, MLX_WINDOW_EVENT, window_hook,
		mlx->screen.connection);
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
