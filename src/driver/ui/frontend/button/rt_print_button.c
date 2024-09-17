/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_print_button.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bonsthie <bonsthie@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 15:38:57 by babonnet          #+#    #+#             */
/*   Updated: 2024/09/17 15:56:12 by bonsthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "__rt_button.h"
#include "mlx.h"
#include "rt_driver.h"
#include <stdio.h>

void	print_button_top_txt(t_screen *screen, t_button *button_top,
		int *pixel_padding)
{
	uint32_t						x;
	uint32_t						y;
	uint32_t						button_size_width;
	struct s_rtss_button_settings	settings;

	settings = rt_get_button_settings(button_top);
	y = settings.margin.top;
	button_size_width = 0;
	while (y < settings.height)
	{
		x = *pixel_padding;
		button_size_width = settings.width + settings.padding.left
			+ settings.padding.right;
		while (x < button_size_width + *pixel_padding)
		{
			mlx_pixel_put(screen->mlx, screen->win, x, y, settings.color);
			x++;
		}
		y++;
	}
	*pixel_padding += settings.margin.left;
	mlx_string_put(screen->mlx, screen->win, *pixel_padding
		+ settings.padding.left, settings.padding.top, 0xFF000000,
		button_top->settings.text);
	*pixel_padding += button_size_width + settings.margin.right;
}

void	rt_print_button(t_screen *screen)
{
	t_button		*button_top;
	int				pixel_padding;

	if (!screen)
		return ;
	button_top = screen->button_top;
	if (!button_top)
		return ;
	pixel_padding = 0;
	while (button_top)
	{
			print_button_top_txt(screen, button_top, &pixel_padding);
		button_top = button_top->next;
	}
}
