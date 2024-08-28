/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_hook_mouse_up.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bonsthie <bonsthie@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 13:59:42 by babonnet          #+#    #+#             */
/*   Updated: 2024/08/28 15:27:08 by bonsthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../_hook.h"
#include "rt_driver.h"
#include <stdio.h>

void	click_to_however(t_button *button)
{
	while (button)
	{
		if (button->action != SLEEP)
		{
			if (button->settings.id == (uint8_t)RT_SIMPLE_BUTTON)
			{
				printf("simple");
				button->action = SLEEP;
			}
			else
				button->action = CLICK;
			button->settings.f(button->settings.data);
			return ;
		}
		button = button->next;
	}
}

void	mouseup_hook_top_bar(int key, t_screen *screen)
{
	(void)key;
	(void)screen;
	if (key == MOUSE_LEFT)
	{
		click_to_however(screen->button_top);
		rt_print_button(screen);
	}
}

void	mouseup_hook_side_bar(int key, t_screen *screen)
{
	(void)key;
	(void)screen;
}

void	mouseup_hook_scene(int key, t_screen *screen)
{
	void				**func;
	t_hooks_function	mouseup_func;
	
	func = screen->hooks.hook_function[RT_MOUSEUP];
	if (func && *func)
	{
		mouseup_func = *func;
		mouseup_func(key, screen->hooks.data[RT_MOUSEUP]);
	}
}


int	rt_mouseup_hook(int key, void *data)
{
	t_screen			*screen;

	screen = data;
	if (screen->mouse_y <= RT_UI_TOP_BAR)
		mouseup_hook_top_bar(key, screen);
	else if (screen->mouse_x >= RT_WIDTH + RT_UI_SIDE_BAR)
		mouseup_hook_side_bar(key, screen);
	else
		mouseup_hook_scene(key, screen);
	rt_mouse_show();
	return (0);
}
