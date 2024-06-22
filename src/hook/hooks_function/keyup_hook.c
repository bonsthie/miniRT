/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyup_hook.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 22:13:03 by babonnet          #+#    #+#             */
/*   Updated: 2024/06/22 17:34:07 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../_hook.h"
#include "miniRT.h"
#include "rt_driver.h"
#include "rt_mesh_obj.h"
#include <rt_scene_elements.h>
#include <sys/types.h>

static void	move_cam(t_scene *data, t_v4f move)
{
	data->cam->coord_axes = move;
}

static void	zoom(t_camera *cam, float new_scale)
{
	cam->zoom *= new_scale;
}

int keyup_hook(int key, void *data)
{
	struct s_hook_data *hdata;

	hdata = data;
	if (key == 22)// S_KEY)
		move_cam(hdata->scene, (t_v4f){0, -5, 0, 0});
	if (key == 26)// Z_KEY)
		move_cam(hdata->scene, (t_v4f){0, 5, 0, 0});
	if (key == 7)// Q_KEY)
		move_cam(hdata->scene, (t_v4f){-5, 0, 0, 0});
	if (key == 4)// D_KEY)
		move_cam(hdata->scene, (t_v4f){5, 0, 0, 0});
	if (key == 20)// A_KEY)
		zoom(hdata->scene->cam, 1.2);
	if (key == 8)// E_KEY)
		zoom(hdata->scene->cam, 1. / 1.2);
	return (0);
}
