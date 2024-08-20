/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_hook.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 15:05:05 by babonnet          #+#    #+#             */
/*   Updated: 2024/08/20 18:24:41 by bonsthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../_rt_mlx.h"
#include "_hook.h"
#include "rt_driver.h"
#include <mlx.h>

void	rt_on_event(t_screen *screen, rt_event_type type, void **f, void *data)
{
	screen->hooks.hook_function[type] = f;
	screen->hooks.data[type] = data;
}

void	hook(t_mlx *mlx)
{
	mlx_on_event(mlx->screen->mlx, mlx->screen->win, MLX_WINDOW_EVENT,
		rt_window_hook, mlx->screen->mlx);
	mlx_on_event(mlx->screen->mlx, mlx->screen->win, MLX_KEYDOWN, rt_keyup_hook,
		mlx->screen);
	mlx_on_event(mlx->screen->mlx, mlx->screen->win, MLX_MOUSEDOWN,
		rt_mousedown_hook, mlx);
	mlx_on_event(mlx->screen->mlx, mlx->screen->win, MLX_MOUSEUP,
		rt_mouseup_hook, mlx->screen);
	// mlx_on_event(mlx->connection, mlx->window, MLX_MOUSEWHEEL, rt_mousewheel_hook, NULL);
}
