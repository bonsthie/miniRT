/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_object.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 15:43:19 by babonnet          #+#    #+#             */
/*   Updated: 2024/05/31 16:55:34 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "scene_elements.h"

void	add_object(void *object, t_file_type file_type)
{
	t_scene		*scene;
	t_object	*new_obj;

	scene = get_scene();
	new_obj = malloc(sizeof(t_object));
	if (!new_obj)
	{
		free(object);
		exit(1);
	}
	new_obj->object = object;
	new_obj->file_type = file_type;
	new_obj->next = scene->object;
	if (!scene->object)
	{
		scene->object = new_obj;
		return ;
	}
	while (scene->object->next)
		scene->object = scene->object->next;
	scene->object->next = new_obj;
}
