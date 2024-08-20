/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_get_color_under_cursor.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 15:44:07 by babonnet          #+#    #+#             */
/*   Updated: 2024/08/19 16:24:35 by bonsthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../_rt_mlx.h"
#include "rt_driver.h"

int	rt_get_color_under_cursor(t_screen *screen, t_img *img)
{
	return (img->color[screen->mouse_y][screen->mouse_x]);
}

int	rt_get_color_under_cursor_avrege(t_screen *screen, t_img *img, int size)
{
	int	x;
	int	y;
	int	temp_y;
	int	result;

	x = screen->mouse_x - size;
	if (x < 0)
		x = 0;
	temp_y = screen->mouse_y - size;
	if (temp_y < 0)
		temp_y = 0;
	result = 0;
	while (x < screen->mouse_x + size && screen->mouse_x + size < RT_WIDTH)
	{
		y = temp_y;
		while (y < screen->mouse_y + size && screen->mouse_y + size < RT_HEIGHT)
		{
			result += img->color[y][x];
			y++;
		}
		x++;
	}
	return (result);
}
