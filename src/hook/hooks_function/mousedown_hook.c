/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mousedown_hook.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 22:13:03 by babonnet          #+#    #+#             */
/*   Updated: 2024/06/22 16:23:10 by yroussea         ###   ########.fr       */
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
		during_right_clic(true, hdata);
	}
	if (key == MOUSE_LEFT)
	{
		during_left_clic(true, hdata);
	}
	return (0);
}
