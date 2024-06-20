/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouseup_hook.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 22:13:03 by babonnet          #+#    #+#             */
/*   Updated: 2024/06/20 23:43:53 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <rt_driver.h>
#include <rt_mesh_obj.h>
#include "../_hook.h"
#include "miniRT.h"

t_rotation	during_right_clic(bool up, void *data)
{
	static bool			active = 0;
	static t_int_vec4	pos;
	t_screen			*screen;
	t_rotation			rot;

	screen = data;
	if (up)
	{
		active = 1 - active;
		rt_mouse_get_pos(screen, &pos.x, &pos.y);
		if (active)
			rt_mouse_hide();
		else
			rt_mouse_show();
		return ((t_rotation){0, 0, 0});
	}
	if (!active)
		return ((t_rotation){0, 0, 0});
	rt_mouse_get_pos(screen, &pos.z, &pos.w);
	rot = (t_rotation){(float)(pos.w - pos.y)/RT_HEIGHT*360,
		(float)(pos.x - pos.z)/RT_WIDTH*360, 0};
	rt_mouse_move(screen, pos.x, pos.y);
	return (rot);
}

int mouseup_hook(int key, void *data)
{
	struct s_hook_data *hdata;

	hdata = data;
	if (key == MOUSE_MIDDLE)
	{
		during_right_clic(1, hdata->screen);
	}
	return (0);
}
