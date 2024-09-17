/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_button_under_cursor.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bonsthie <bonsthie@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 15:09:51 by bonsthie          #+#    #+#             */
/*   Updated: 2024/09/11 21:23:23 by bonsthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "__rt_button.h"

t_button	*get_button_under_cursor_top(t_screen *screen)
{
	t_button			*button;
	struct s_rtss_button_settings settings;
	int					start_button_width;
	int					button_size_width;

	button = screen->button_top;

	if (!button)
		return (NULL);
	settings = rt_get_button_settings(button);
	start_button_width = settings.margin.left;
	while (button)
	{
		button_size_width = settings.width + settings.padding.left + settings.padding.right;
		if (screen->mouse_x >= start_button_width
			&& screen->mouse_x <= button_size_width + start_button_width)
			return (button);
		start_button_width += button_size_width + settings.margin.right;
		button = button->next;
		if (button)
			settings = rt_get_button_settings(button);
	}
	return (NULL);
}
