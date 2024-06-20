/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mousedown_hook.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 22:13:03 by babonnet          #+#    #+#             */
/*   Updated: 2024/06/20 23:41:57 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../_hook.h"
#include "miniRT.h"

int mousedown_hook(int key, void *data)
{
	struct s_hook_data *hdata;

	hdata = data;
	if (key == MOUSE_MIDDLE)
	{
		during_right_clic(1, hdata->screen);
	}
	(void)key;
	(void)data;
	return (0);
}
