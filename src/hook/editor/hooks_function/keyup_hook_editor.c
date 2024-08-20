/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyup_hook_editor.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 22:13:03 by babonnet          #+#    #+#             */
/*   Updated: 2024/08/20 14:31:35 by bonsthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../_hook.h"
#include "miniRT.h"
#include "rt_driver.h"
#include <rt_scene_elements.h>
#include <sys/types.h>

static void	move_cam(t_scene *data, t_v4f move)
{
	data->cam.coord_axes = move;
}

static void	zoom(t_camera *cam, float new_scale)
{
	cam->zoom *= new_scale;
}

int keyup_hook_editor(int key, void *data)
{
	struct s_hook_data *hdata;
	t_status *status;

	hdata = data;
	status = &hdata->scene->status;
	if (key == T_KEY)
		status->gizmo_selected = GIZMO_TRANSLATE;
	else if (key == R_KEY)
		status->gizmo_selected = GIZMO_ROTATE;
	else if (key == S_KEY)
		status->gizmo_selected = GIZMO_SCALE;
	else if (key == DOWN_ARROW)
		move_cam(hdata->scene, (t_v4f){0, -5, 0, 0});
	else if (key == UP_ARROW)
		move_cam(hdata->scene, (t_v4f){0, 5, 0, 0});
	else if (key == L_ARROW)
		move_cam(hdata->scene, (t_v4f){-5, 0, 0, 0});
	else if (key == R_ARROW)
		move_cam(hdata->scene, (t_v4f){5, 0, 0, 0});
	else if (key == A_KEY)
		zoom(&hdata->scene->cam, 1.2);
	else if (key == E_KEY)
		zoom(&hdata->scene->cam, 1. / 1.2);
	else if (key == ESCAPE)
		status->object_selected_id = 0;
	return (0);
}
