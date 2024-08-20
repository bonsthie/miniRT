/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_clear_img.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bonsthie <bonsthie@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 16:24:33 by bonsthie          #+#    #+#             */
/*   Updated: 2024/08/19 16:24:35 by bonsthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../_rt_mlx.h"
#include <libft.h>

void	rt_set_image_color(t_img *img, unsigned int color)
{
	int	y;
	int	x;

	y = 0;
	while (y < RT_HEIGHT)
	{
		x = 0;
		while (x < RT_WIDTH)
		{
			img->zbuffer[y][x] = SHORT_MAX;
			img->color[y][x] = color;
			img->obj_id[y][x] = 0;
			x++;
		}
		y++;
	}
}
