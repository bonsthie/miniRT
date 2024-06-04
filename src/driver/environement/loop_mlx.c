/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 18:14:03 by babonnet          #+#    #+#             */
/*   Updated: 2024/06/05 01:12:31 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../_rt_mlx.h"
#include "mlx.h"

#include <libft.h>
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

static int _loop(void *data)
{
	t_mlx *mlx;

	mlx = data;
	update_img(mlx->img);
	mlx->scene_function(mlx->scene, mlx->img, &mlx->screen);
	return (0);
}

int rt_loop(t_scene *scene, int loop(t_scene *scene, t_img *img, t_screen *screen))
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
	mlx_loop_hook(mlx.screen.connection, _loop, &mlx);
	mlx_loop(mlx.screen.connection);
	free(mlx.img);
	mlx_clear_window(mlx.screen.connection, mlx.screen.window);
	mlx_destroy_display(mlx.screen.connection);
	return (0);
}

