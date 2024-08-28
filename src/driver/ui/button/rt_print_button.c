/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_print_button.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bonsthie <bonsthie@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 15:38:57 by babonnet          #+#    #+#             */
/*   Updated: 2024/08/28 17:00:26 by bonsthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "__rt_button.h"
#include "mlx.h"
#include "rt_driver.h"
#include <stdio.h>

void	print_button_top_txt(t_screen *screen, t_button *button_top,
		int *pixel_padding, unsigned int color)
{
	int	x;
	int	y;
	int					button_size_width;
	t_button_setting	settings;

	settings = button_top->settings;
	y = settings.margin.top;
	button_size_width = 0;
	while (y < settings.height)
	{
		x = *pixel_padding;
		button_size_width = settings.width + settings.padding.left + settings.padding.right;
		while (x < button_size_width + *pixel_padding)
		{
			mlx_pixel_put(screen->mlx, screen->win, x, y, color);
			x++;
		}
		y++;
	}
	*pixel_padding += settings.margin.left;
	mlx_string_put(screen->mlx, screen->win, *pixel_padding + settings.padding.left, settings.padding.top, 0xFF000000, settings.text);
	*pixel_padding += button_size_width + settings.margin.right;
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
