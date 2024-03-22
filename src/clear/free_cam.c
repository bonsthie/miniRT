/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_cam.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 14:10:36 by babonnet          #+#    #+#             */
/*   Updated: 2024/03/19 14:11:08 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene_elements.h"
#include <stdlib.h>

void free_cam(t_camera *cam)
{
	t_camera *cam_next;

	while (cam)
	{
		cam_next = cam->next;
		free(cam);
		cam = cam_next;
	}
}
