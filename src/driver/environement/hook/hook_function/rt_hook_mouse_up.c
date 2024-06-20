/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_hook_mouse_up.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 13:59:42 by babonnet          #+#    #+#             */
/*   Updated: 2024/06/20 23:10:01 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../_hook.h"
#include "rt_driver.h"

void click_to_however(t_button *button)
{
	while (button)
	{
		if (button->action == CLICK)
		{
			button->func(button->data);
			button->action = SLEEP;
			return ;
		}
		button = button->next;
	}
}

void mouseup_hook_top_bar(int key, t_screen *screen)
{
	(void)key;
	(void)screen;
	if (key == MOUSE_LEFT)
	{
		click_to_however(screen->button_top);
		rt_print_button(screen);
	}

}

int rt_mouseup_hook(int key, void *data)
{
	t_screen *screen;

	screen = data;
	mouseup_hook_top_bar(key, screen);
	if (screen->hooks.hook_function[RT_MOUSEUP])
		screen->hooks.hook_function[RT_MOUSEUP](key, screen->hooks.data[RT_MOUSEUP]);
	return (0);

}
