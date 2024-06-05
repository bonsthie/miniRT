/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_loop.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 18:14:03 by babonnet          #+#    #+#             */
/*   Updated: 2024/06/05 17:11:30 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../_rt_mlx.h"
#include "mlx.h"
#include "rt_driver.h"

#include <libft.h>
#include <rt_scene_elements.h>

static void update_img(t_img *img)
{
	int y;
	int x;

	y = 0;
	while (y < RT_HEIGHT)
	{
		x = 0;
		while (x < RT_WIDTH)
		{
			img->zbuffer[y][x] = INT_MAX;
			img->color[y][x] = RT_BACKGROUND_COLOR;
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
	mlx->scene_function(mlx->scene, mlx->img, mlx->screen);
	return (0);
}

int rt_loop(t_scene *scene, t_screen *screen, int loop(t_scene *scene, t_img *img, t_screen *screen))
{
	t_mlx mlx;

	mlx.img = malloc(sizeof(t_img));
	if (!mlx.img)
		return (1);
	mlx.scene = scene;
	mlx.scene_function = loop;
	mlx.screen = screen;
	hook(&mlx);
	rt_print_ui_screen(mlx.screen);
	rt_print_button(screen);
	mlx_loop_hook(screen->mlx, _loop, &mlx);
	mlx_loop(screen->mlx);
	free(mlx.img);
	return (0);
}

