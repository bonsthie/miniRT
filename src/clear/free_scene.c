/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 13:14:36 by babonnet          #+#    #+#             */
/*   Updated: 2024/03/22 16:25:50 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "free_int.h"

void	__attribute__((destructor)) free_scene(void)
{
	t_scene	*scene;

	scene = get_scene();
	if (scene->cam)
		free_cam(scene->cam);
	if (scene->light)
		free_light(scene->light);
	if (scene->object)
		free_object(scene->object);
}
