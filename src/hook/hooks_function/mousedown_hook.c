/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mousedown_hook.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 22:13:03 by babonnet          #+#    #+#             */
/*   Updated: 2024/06/22 23:12:29 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../_hook.h"
#include "libft.h"
#include "miniRT.h"
#include "rt_driver.h"
#include "rt_scene_elements.h"

int mousedown_hook(int key, void *data)
{
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
		if (status->object_selected_id == 0)
		{
			rt_mouse_hide();
			move_scene_during_left_clic(true, hdata);
		}
			
	}
	return (0);
}
