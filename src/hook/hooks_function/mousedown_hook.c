/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mousedown_hook.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 22:13:03 by babonnet          #+#    #+#             */
/*   Updated: 2024/07/26 18:11:47 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../_hook.h"
#include "miniRT.h"
#include "rt_driver.h"
#include "rt_scene_elements.h"
#include <stdio.h>

bool gizmo_axe_selected(t_scene *scene, t_screen *screen)
{
	union u_color color;

	color.value = rt_get_color_under_cursor_avrege(screen, scene->asset.gizmo_img, 10);
	if (color.value == 0)
		return (false);
	if (color.components.red > color.components.green && color.components.red > color.components.blue)
	{
		scene->status.gizmo_axe_selected = GIZMO_AXE_X;
		return (true);
	}
	else if (color.components.green > color.components.red && color.components.green > color.components.blue)
	{
		scene->status.gizmo_axe_selected = GIZMO_AXE_Y;
		return (true);
	}
	else if (color.components.blue > color.components.red && color.components.blue > color.components.green)
	{
		scene->status.gizmo_axe_selected = GIZMO_AXE_Z;
		return (true);
	}
	return (false);
}

int mousedown_hook(int key, void *data)
{
	static short		id_selected = 0;
	struct s_hook_data *hdata;
	t_status			*status;

	hdata = data;
	status = &hdata->scene->status;
	if (key == MOUSE_MIDDLE)
	{
		status->mouse_right_press = true;
		rt_mouse_hide();
		move_scene_during_right_clic(true, hdata);
	}
	if (key == MOUSE_LEFT)
	{
		if (gizmo_axe_selected(hdata->scene, hdata->screen) == false)
		{
			status->mouse_left_press = true;
			status->object_selected_id = rt_id_obj_under_curssor(hdata->screen, hdata->img);
			if (status->object_selected_id != id_selected && status->object_selected_id)
				id_selected = status->object_selected_id;
			printf("obj clicked %d\n", status->object_selected_id);

			if (status->object_selected_id == 0)
			{
				id_selected = 0;
				rt_mouse_hide();
				move_scene_during_left_clic(true, hdata);
			}
		}
	}
	return (0);
}
