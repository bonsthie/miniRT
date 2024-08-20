/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_print_ui.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bonsthie <bonsthie@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 16:24:33 by bonsthie          #+#    #+#             */
/*   Updated: 2024/08/19 16:24:35 by bonsthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../_rt_mlx.h"
#include "mlx.h"
#include "rt_driver.h"

static void	print_side_ui_background(t_screen *screen)
{
	int	x;
	int	y;

	y = RT_UI_TOP_BAR;
	while (y < RT_HEIGHT)
	{
		x = RT_WIDTH - RT_UI_SIDE_BAR;
		while (x < RT_WIDTH)
		{
			mlx_pixel_put(screen->mlx, screen->win, x, y, RT_UI_SIDE_BAR_COLOR);
			x++;
		}
		y++;
	}
}

static void	print_top_ui_background(t_screen *screen)
{
	int	x;
	int	y;

	y = 0;
	while (y < RT_UI_TOP_BAR)
	{
		x = 0;
		while (x < RT_WIDTH)
		{
			mlx_pixel_put(screen->mlx, screen->win, x, y, RT_UI_TOP_BAR_COLOR);
			x++;
		}
		y++;
	}
}

void	rt_print_ui_screen(t_screen *screen)
{
	print_top_ui_background(screen);
	print_side_ui_background(screen);
	rt_print_button(screen);
}
