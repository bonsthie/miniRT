/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyup_hook.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 22:13:03 by babonnet          #+#    #+#             */
/*   Updated: 2024/06/22 15:00:45 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../_hook.h"
#include "miniRT.h"
#include "rt_driver.h"
#include <rt_scene_elements.h>

void	move_cam(t_scene *data, t_v4f move)
{
	data->cam.coord += move;
}


int keyup_hook(int key, void *data)
{
	struct s_hook_data *hdata;

	hdata = data;
	if (key == S_KEY)
		move_cam(hdata->scene, (t_v4f){-1, 0, 0, 0});
	if (key == Z_KEY)
		move_cam(hdata->scene, (t_v4f){1, 0, 0, 0});
	return (0);
}
