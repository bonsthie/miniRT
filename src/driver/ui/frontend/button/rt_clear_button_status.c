/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_clear_button_status.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bonsthie <bonsthie@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 16:24:33 by bonsthie          #+#    #+#             */
/*   Updated: 2024/08/19 16:24:35 by bonsthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "__rt_button.h"
#include "rt_driver.h"

void	reset_however_button(t_screen *screen)
{
	t_button	*button;

	button = screen->button_top;
	while (button)
	{
		if (button->action == HOWEVER)
			button->action = SLEEP;
		button = button->next;
	}
	button = screen->button_side;
	while (button)
	{
		if (button->action == HOWEVER)
			button->action = SLEEP;
		button = button->next;
	}
}
