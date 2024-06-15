/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 15:05:05 by babonnet          #+#    #+#             */
/*   Updated: 2024/06/10 13:58:30 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>

#include "_hook.h"
#include "../../_rt_mlx.h"

void	hook(t_mlx *mlx)
{
	mlx_on_event(mlx->screen->mlx, mlx->screen->win, MLX_WINDOW_EVENT, window_hook, mlx->screen->mlx);
	mlx_on_event(mlx->screen->mlx, mlx->screen->win, MLX_KEYDOWN, keyup_hook, mlx->screen);
	mlx_on_event(mlx->screen->mlx, mlx->screen->win, MLX_MOUSEDOWN, mousedown_hook, mlx->screen);
	mlx_on_event(mlx->screen->mlx, mlx->screen->win, MLX_MOUSEUP, mouseup_hook, mlx->screen);
	// mlx_on_event(mlx->connection, mlx->window, MLX_MOUSEWHEEL,
	//	mousewheel_hook,
	//	NULL);
}
