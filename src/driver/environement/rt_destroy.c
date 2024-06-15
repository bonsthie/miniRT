/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_destroy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 11:37:27 by babonnet          #+#    #+#             */
/*   Updated: 2024/06/10 18:46:03 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../_rt_mlx.h"
#include "rt_driver.h"
#include <signal.h>
#include <mlx.h>

void rt_destroy(t_screen *screen)
{
	t_button *tmp;

	kill(screen->error_pid, SIGTERM);
	mlx_clear_window(screen->mlx, screen->win);
	/* mlx_destroy_display(screen->mlx); */
	while (screen->button_top)
	{
		tmp = screen->button_top->next;
		free(screen->button_top);
		screen->button_top = tmp;
	}
	while (screen->button_side)
	{
		tmp = screen->button_side->next;
		free(screen->button_side);
		screen->button_side = tmp;
	}
	free(screen);
}
