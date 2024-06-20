/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_button.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 15:23:44 by babonnet          #+#    #+#             */
/*   Updated: 2024/06/05 19:24:52 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "rt_driver.h"
#include "../_rt_mlx.h"

t_button *button_last(t_button *button_top)
{
	t_button *last;

	last = button_top;
	while (button_top)
	{
		last = button_top;
		button_top = button_top->next;
	}
	return (last);
}

void rt_add_text_button_top(t_screen *screen, char *text, void *data, void f(void *))
{
	t_button *button_top;
	t_button *new_button;

	new_button = malloc(sizeof(t_button));
	if (!new_button)
		return ;
	new_button->data = data;
	new_button->type = TXT;
	new_button->func = f;
	new_button->name = ft_strdup(text);
	new_button->next = NULL;
	new_button->action = SLEEP;
	button_top = screen->button_top;
	if (!button_top)
	{
		screen->button_top = new_button;
		return ;
	}
	button_last(button_top)->next = new_button;
}
