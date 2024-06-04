/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 18:14:03 by babonnet          #+#    #+#             */
/*   Updated: 2024/06/04 19:28:22 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_rt_mlx.h"
#include "mlx.h"

#include <stdio.h>
#include <libft.h>
#include <linux/limits.h>
#include <rt_scene_elements.h>

static void update_img(t_img *img)
{
	int y;
	int x;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			img->zbuffer[y][x] = INT_MAX;
			img->color[y][x] = 0;
			x++;
		}
		y++;
	}
}

static void print_img(t_mlx *mlx, t_img *img)
{
	int y;
	int x;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			mlx_pixel_put(mlx->connection, mlx->window, x, y, img->color[y][x]);
			x++;
		}
		y++;
	}

}

static int _loop(void *data)
{
	t_mlx *mlx;

	mlx = data;
	update_img(mlx->img);
	mlx->scene_function(mlx->scene, mlx->img);
	mlx_clear_window(mlx->connection, mlx->window);
	print_img(mlx, mlx->img);
	return (0);
}

int rt_loop(t_scene *scene, int loop(t_scene *scene, t_img *img))
{
	t_mlx mlx;

	mlx.img = malloc(sizeof(t_img));
	if (!mlx.img)
		return (1);
	if (init_mlx_data(&mlx))
	{
		free(mlx.img);
		return (1);
	}
	mlx.scene = scene;
	mlx.scene_function = loop;
	hook(&mlx);
	mlx_loop_hook(mlx.connection, _loop, &mlx);
	mlx_loop(mlx.connection);
	return (0);
}

