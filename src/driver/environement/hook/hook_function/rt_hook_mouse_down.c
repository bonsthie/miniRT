/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_hook_mouse_down.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bonsthie <bonsthie@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 16:24:33 by bonsthie          #+#    #+#             */
/*   Updated: 2024/08/20 19:11:27 by bonsthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../_hook.h"
#include "rt_driver.h"
#include <object.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

void	untoggle_by_id(t_button *button, int id)
{
	while (button)
	{
		if (button->settings.id == id && button->action == CLICK)
			button->action = SLEEP;
		button = button->next;
	}
}

void	however_to_click(t_screen *screen, t_button *button)
{
	t_button	*start_button;

	start_button = button;
	while (button)
	{
		if (button->action == HOWEVER)
		{
			printf("yooo\n");
			untoggle_by_id(start_button, button->settings.id);
			button->action = CLICK;
			rt_print_button(screen);
			return ;
		}
		else if (button->action == CLICK
			&& button->settings.id == (uint8_t)RT_SIMPLE_BUTTON)
		{
			button->action = SLEEP;
			rt_print_button(screen);
			return ;
		}
		button = button->next;
	}
}

void	mousedown_hook_top_bar(int key, t_screen *screen)
{
	if (key == MOUSE_LEFT)
		however_to_click(screen, screen->button_top);
}

void	mousedown_hook_side_bar(int key, t_mlx *mlx)
{
	(void)mlx;
	(void)key;
}

void	change_obj_color(t_object *object, int id)
{
	union u_color	color;

	if (!object || id == 0)
		return ;
	while (object->id != id)
		object = object->next;
	color.value = 0xFFFFFFFF;
	color.components.red = rand() % 255;
	update_color_object(object->object, color.value);
}

void	mousedown_hook_scene(int key, t_screen *screen)
{
	void				**func;
	t_hooks_function	mousedown_func;
	
	func = screen->hooks.hook_function[RT_MOUSEDOWN];
	if (func && *func)
	{
		mousedown_func = *func;
		mousedown_func(key, screen->hooks.data[RT_MOUSEDOWN]);
	}
}

int	rt_mousedown_hook(int key, void *data)
{
	t_mlx				*mlx;
	t_screen			*screen;

	mlx = data;
	screen = mlx->screen;
	if (screen->mouse_y <= RT_UI_TOP_BAR)
		mousedown_hook_top_bar(key, screen);
	else if (screen->mouse_x >= RT_WIDTH + RT_UI_SIDE_BAR)
		mousedown_hook_side_bar(key, mlx);
	else
		mousedown_hook_scene(key, screen);
	return (0);
}
