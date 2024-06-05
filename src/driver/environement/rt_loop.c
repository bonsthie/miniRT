/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_loop.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 18:14:03 by babonnet          #+#    #+#             */
/*   Updated: 2024/06/05 21:20:15 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../_rt_mlx.h"
#include "mlx.h"
#include "rt_driver.h"

#include <libft.h>
#include <stdio.h>
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

void uptade_top_bar_status(t_button *button, int mouse_x)
{
	int offset;
	int count;
	
	count = 0;
	while(button)
	{
		offset = count + ft_strlen(button->name) * 12 + RT_BUTTON_SIDE_PADDING + 2;
		
		if (mouse_x > count && mouse_x <= offset && button->action != CLICK)
			button->action = HOWEVER;
		count = offset;
		button = button->next;
	}
}

void rt_update_ui(t_screen *screen)
{
	reset_however_button(screen);
	if (screen->mouse_y <= RT_UI_TOP_BAR)
	{
		uptade_top_bar_status(screen->button_top, screen->mouse_x);
	}
	rt_print_ui_screen(screen);
}

static int _loop(void *data)
{
	t_mlx *mlx;
	t_screen *screen;

	mlx = data;
	screen = mlx->screen;
	update_img(mlx->img);
	mlx_mouse_get_pos(screen->mlx, &screen->mouse_x, &screen->mouse_y);
	rt_update_ui(screen);
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
	rt_print_ui_screen(screen);
	mlx_loop_hook(screen->mlx, _loop, &mlx);
	mlx_loop(screen->mlx);
	free(mlx.img);
	return (0);
}

