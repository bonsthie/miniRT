/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_add_button.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bonsthie <bonsthie@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 15:23:44 by babonnet          #+#    #+#             */
/*   Updated: 2024/08/22 17:19:55 by bonsthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "__rt_button.h"
#include "rt_driver.h"

t_button	*button_last(t_button *button_top)
{
	t_button	*last;

	last = button_top;
	while (button_top)
	{
		last = button_top;
		button_top = button_top->next;
	}
	return (last);
}

void	rt_add_text_button_top(t_screen *screen, t_button_setting settings)
{
	t_button	*button_top;
	t_button	*new_button;

	new_button = malloc(sizeof(t_button));
	new_button->settings = settings;
	new_button->next = NULL;
	if (!new_button)
		return ;
	button_top = screen->button_top;
	if (!button_top)
	{
		screen->button_top = new_button;
		return ;
	}
	button_last(button_top)->next = new_button;
	if (settings.on_start)
	{
		settings.f(settings.data);
		new_button->action = CLICK;
	}
}
