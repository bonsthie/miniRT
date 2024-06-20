/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_mouse_get_pos.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 22:25:24 by babonnet          #+#    #+#             */
/*   Updated: 2024/06/20 23:09:23 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../_rt_mlx.h"
#include "mlx.h"

int	rt_mouse_get_pos(t_screen *screen, int *x, int *y)
{
	int result;

	result = mlx_mouse_get_pos(screen->mlx, &screen->mouse_x, &screen->mouse_y);
	*x = screen->mouse_x;
	*y = screen->mouse_y;
	return (result);
}
