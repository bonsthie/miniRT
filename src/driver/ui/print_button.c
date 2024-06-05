/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_button.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 15:38:57 by babonnet          #+#    #+#             */
/*   Updated: 2024/06/05 17:39:58 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include <stdio.h>
#include "rt_driver.h"
#include "../_rt_mlx.h"

#define RT_BUTTON_SIDE_PADDING 10

void print_button_top_txt(t_screen *screen, t_button *button_top, int *pixel_padding)
{
	int sidepading;
	int new_sidepading;
	int x;
	int y;
	
	sidepading = RT_UI_TOP_BAR * 0.1;
	y = sidepading;
	*pixel_padding += 5;
	new_sidepading = *pixel_padding + ft_strlen(button_top->name) * 12 + RT_BUTTON_SIDE_PADDING;
	while (y < RT_UI_TOP_BAR - sidepading)
	{
		x = *pixel_padding;
		while (x < new_sidepading)
		{
			mlx_pixel_put(screen->mlx, screen->win, x, y, 0xFFFFFFFF);
			x++;
		}
		y++;
	}
	printf("%s\n", button_top->name);
	*pixel_padding += RT_BUTTON_SIDE_PADDING;
	mlx_string_put(screen->mlx, screen->win, *pixel_padding, sidepading + RT_UI_TOP_BAR * 0.5, 0xFF000000, button_top->name);
	*pixel_padding = new_sidepading;
}

void rt_print_button(t_screen *screen)
{
	t_button	*button_top;
	int			pixel_padding;

	if (!screen)
		return ;
	button_top = screen->button_top;
	if (!button_top)
		return ;
	pixel_padding = 0;
	while (button_top)
	{
		if (button_top->type == TXT)
		{

			print_button_top_txt(screen, button_top, &pixel_padding);
		}
		button_top = button_top->next;
	}
}
