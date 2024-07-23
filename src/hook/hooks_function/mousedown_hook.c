/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mousedown_hook.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 22:13:03 by babonnet          #+#    #+#             */
/*   Updated: 2024/07/23 13:53:43 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../_hook.h"
#include "miniRT.h"
#include "rt_driver.h"
#include "rt_scene_elements.h"
#include <stdio.h>

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
		status->mouse_left_press = true;
		status->object_selected_id = rt_id_obj_under_curssor(hdata->screen, hdata->img);
		if (status->object_selected_id != id_selected && status->object_selected_id)
		{
			printf("fsffs\n");
			// update_gizmo_position(hdata->scene);
			id_selected = status->object_selected_id;
		}
		printf("obj clicked %d\n", status->object_selected_id);
		if (status->object_selected_id == 0)
		{
			id_selected = 0;
			rt_mouse_hide();
			move_scene_during_left_clic(true, hdata);
		}
			
	}
	return (0);
}
