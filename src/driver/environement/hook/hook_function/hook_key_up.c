/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_key_up.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 21:22:31 by babonnet          #+#    #+#             */
/*   Updated: 2024/06/20 21:54:02 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include "../_hook.h"
#include "rt_driver.h"


int keyup_hook(int key, void *data)
{
	t_screen *screen;

	screen = data;
	if (key == L_KEY)
	{
		rt_error_window(screen, "Luke jtm bb inferieur a trois");
	}
	if (key == ESCAPE)
		mlx_loop_end(screen->mlx);
	if (screen->hooks.hook_function[RT_KEYUP])
		screen->hooks.hook_function[RT_KEYUP](key, screen->hooks.data[RT_KEYUP]);
	return (0);
}
