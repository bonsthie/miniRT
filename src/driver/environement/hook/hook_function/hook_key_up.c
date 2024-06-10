/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_key_up.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 21:22:31 by babonnet          #+#    #+#             */
/*   Updated: 2024/06/09 21:34:48 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <signal.h>
#include <stdio.h>
#include "../_hook.h"


int keyup_hook(int key, void *data)
{
	t_screen *screen;

	screen = data;
	if (key == A_KEY)
	{
		union sigval sv;
		sv.sival_ptr = "press A";
		sigqueue(screen->error_pid, SIGUSR1, sv);
	}
	if (key == ESCAPE)
		mlx_loop_end(screen->mlx);
	return (0);
}
