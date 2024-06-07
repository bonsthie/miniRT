/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_key_up.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 21:22:31 by babonnet          #+#    #+#             */
/*   Updated: 2024/06/07 22:15:19 by babonnet         ###   ########.fr       */
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
		kill(screen->error_pid, SIGUSR1);
	}
	return (0);
}
