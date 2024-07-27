/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouseup_hook.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 22:13:03 by babonnet          #+#    #+#             */
/*   Updated: 2024/07/26 18:42:05 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <rt_driver.h>
#include <rt_mesh_obj.h>
#include "../_hook.h"
#include "miniRT.h"
#include "rt_scene_elements.h"

void	move_scene_during_right_clic(bool up, struct s_hook_data *hdata)
{
	static bool			active = false;
	static t_int_vec4	pos;
	t_camera			*cam;

	if (hdata->scene->cam.move_usage & (ZOOM | MOVING))
		return ;
	if (up == true)
	{
		active = 1 - active;
		hdata->scene->cam.move_usage = 1u << (active * 2);
		rt_mouse_get_pos(hdata->screen, &pos.x, &pos.y);
		return ;
	}
	if (!active)
		return ;
	cam = &hdata->scene->cam;
	rt_mouse_get_pos(hdata->screen, &pos.z, &pos.w);
	rt_mouse_move(hdata->screen, pos.x, pos.y);
	cam->rotation = (t_rotation){
		cam->rotation.pitch + (float)(pos.w - pos.y)/RT_HEIGHT*360,
		cam->rotation.yaw + (float)(pos.x - pos.z)/RT_WIDTH*360,
		cam->rotation.roll + 0};
}

void	move_scene_during_left_clic(bool up, struct s_hook_data *hdata)
{
	static bool			active = false;
	static t_int_vec4	pos;
	t_camera			*cam;

	if (hdata->scene->cam.move_usage & (ZOOM | ROTATE))
		return ;
	if (up == true)
	{
		active = 1 - active;
		hdata->scene->cam.move_usage = 1u << (active * 3);
		rt_mouse_get_pos(hdata->screen, &pos.x, &pos.y);
		return ;
	}
	if (!active)
		return ;
	cam = &hdata->scene->cam;
	rt_mouse_get_pos(hdata->screen, &pos.z, &pos.w);
	rt_mouse_move(hdata->screen, pos.x, pos.y);
	cam->coord_translation += (t_v4f){
		(float)(pos.z - pos.x)/10,
		(float)(pos.w - pos.y)/10,
		0, 0};
}

int mouseup_hook(int key, void *data)
{
	struct s_hook_data *hdata;
	t_status			*status;

	hdata = data;
	status = &hdata->scene->status;
	if (key == MOUSE_MIDDLE)
	{
		status->mouse_right_press = false;
		move_scene_during_right_clic(true, hdata);
		rt_mouse_show();
	}
	if (key == MOUSE_LEFT)
	{
		status->gizmo_axe_selected = 0;
		status->mouse_left_press = false;
		move_scene_during_left_clic(true, hdata);
		rt_mouse_show();
	}
	return (0);
}
