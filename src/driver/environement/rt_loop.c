/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_loop.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bonsthie <bonsthie@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 18:14:03 by babonnet          #+#    #+#             */
/*   Updated: 2024/08/28 15:25:44 by bonsthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../_rt_mlx.h"
#include "mlx.h"
#include "rt_driver.h"
#include <libft.h>
#include <rt_scene_elements.h>

void	uptade_top_bar_status(t_screen *screen)
{
	t_button *button;

	button = get_button_under_cursor_top(screen);
	if (!button)
		return ;
	if (button->action != CLICK)
		button->action = HOWEVER;
}

int	has_a_button_click(t_screen *screen)
{
	t_button	*button;

	button = screen->button_top;
	while (button)
	{
		if (button->action == CLICK)
		{
			button->action = SLEEP;
			return (1);
		}
		button = button->next;
	}
	return (0);
}

void	rt_update_ui(t_screen *screen)
{
	reset_however_button(screen);
	if (screen->mouse_y <= RT_UI_TOP_BAR + 30)
	{
		if (screen->mouse_y <= RT_UI_TOP_BAR)
			uptade_top_bar_status(screen);
		rt_print_ui_screen(screen);
	}
}

static int	_loop(void *data)
{
	t_mlx		*mlx;
	t_screen	*screen;

	mlx = data;
	screen = mlx->screen;
	rt_set_image_color(mlx->img, RT_BACKGROUND_COLOR);
	rt_mouse_get_pos(screen, &screen->mouse_x, &screen->mouse_y);
	rt_update_ui(screen);
	mlx->scene_function(mlx->data, mlx->img, mlx->screen);
	return (0);
}

int	rt_loop(void *data, t_screen *screen, int loop(void *data, t_img *img,
			t_screen *screen))
{
	t_mlx	mlx;

	mlx.img = malloc(sizeof(t_img));
	if (!mlx.img)
		return (1);
	mlx.data = data;
	mlx.scene_function = loop;
	mlx.screen = screen;
	hook(&mlx);
	rt_print_ui_screen(screen);
	mlx_loop_hook(screen->mlx, _loop, &mlx);
	mlx_loop(screen->mlx);
	free(mlx.img);
	return (0);
}
