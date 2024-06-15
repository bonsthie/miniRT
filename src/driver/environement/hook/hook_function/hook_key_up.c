/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_key_up.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 21:22:31 by babonnet          #+#    #+#             */
/*   Updated: 2024/06/10 13:51:21 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <signal.h>
#include <stdio.h>
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
	return (0);
}
