/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_print_button.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bonsthie <bonsthie@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 15:38:57 by babonnet          #+#    #+#             */
/*   Updated: 2024/08/19 16:24:35 by bonsthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "__rt_button.h"
#include "mlx.h"
#include "rt_driver.h"
#include <stdio.h>

void	print_button_top_txt(t_screen *screen, t_button *button_top,
		int *pixel_padding, unsigned int color)
{
	int	sidepading;
	int	new_sidepading;
	int	x;
	int	y;

	sidepading = RT_UI_TOP_BAR * 0.1;
	y = sidepading;
	*pixel_padding += 4;
	new_sidepading = *pixel_padding + ft_strlen(button_top->settings.text) * 12
		+ RT_BUTTON_SIDE_PADDING;
	while (y < RT_UI_TOP_BAR - sidepading)
	{
		x = *pixel_padding;
		while (x < new_sidepading)
		{
			mlx_pixel_put(screen->mlx, screen->win, x, y, color);
			x++;
		}
		y++;
	}
	*pixel_padding += RT_BUTTON_SIDE_PADDING;
	mlx_string_put(screen->mlx, screen->win, *pixel_padding
		+ RT_BUTTON_SIDE_PADDING * 0.2, sidepading + RT_UI_TOP_BAR * 0.5,
		0xFF000000, button_top->settings.text);
	*pixel_padding = new_sidepading;
}

void	rt_print_button(t_screen *screen)
{
	t_button		*button_top;
	int				pixel_padding;
	unsigned int	color;

	if (!screen)
		return ;
	button_top = screen->button_top;
	if (!button_top)
		return ;
	pixel_padding = 0;
	while (button_top)
	{
		if (button_top->action == HOWEVER)
			color = RT_BUTTON_COLOR_HOWEVER;
		else if (button_top->action == CLICK)
		{
			color = RT_BUTTON_COLOR_CLICK;
		}
		else
			color = RT_BUTTON_COLOR;
		if (button_top->settings.style == TEXT)
		{
			print_button_top_txt(screen, button_top, &pixel_padding, color);
		}
		button_top = button_top->next;
	}
}
