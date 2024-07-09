/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_put_pixel.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 16:54:38 by babonnet          #+#    #+#             */
/*   Updated: 2024/06/25 17:09:47 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_driver.h"

int rt_put_pixel_img(t_img *img, int x, int y, int z, int color)
{
	img->color[y][x] = color;
	img->zbuffer[y][x] = z;
	return (0);
}

int rt_put_pixel_img_protected(t_img *img, int x, int y, int z, int color)
{
	if (x < 0 || x >= RT_WIDTH || y < 0 || y >= RT_HEIGHT)
		return (1);
	img->color[y][x] = color;
	img->zbuffer[y][x] = z;
	return (0);
}
