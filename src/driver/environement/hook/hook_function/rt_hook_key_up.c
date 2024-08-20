/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_hook_key_up.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 21:22:31 by babonnet          #+#    #+#             */
/*   Updated: 2024/08/20 18:26:08 by bonsthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../_hook.h"
#include "rt_driver.h"
#include <mlx.h>

int	rt_keyup_hook(int key, void *data)
{
	t_screen			*screen;
	t_hooks_function	keyup_func;

	screen = data;
	if (key == L_KEY)
	{
		rt_error_window("Luke jtm bb inferieur a trois");
	}
	if (screen->hooks.hook_function[RT_KEYUP])
	{
		keyup_func = *screen->hooks.hook_function[RT_KEYUP];
		keyup_func(key, screen->hooks.data[RT_KEYUP]);
	}
	return (0);
}
