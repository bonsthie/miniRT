/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_destroy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 11:37:27 by babonnet          #+#    #+#             */
/*   Updated: 2024/06/05 14:52:20 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../_rt_mlx.h"
#include <mlx.h>

void rt_destroy(t_screen *screen)
{
	mlx_clear_window(screen->mlx, screen->win);
	mlx_destroy_display(screen->mlx);
	free(screen);
}
