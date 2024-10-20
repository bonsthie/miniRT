/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_object.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 15:43:19 by babonnet          #+#    #+#             */
/*   Updated: 2024/08/19 16:24:36 by bonsthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>
#include <rt_scene_elements.h>
#include <stdio.h>

void	add_object(t_scene *scene, void *object, t_file_type file_type)
{
	t_object	*new_obj;
	t_object	*old_obj;

	new_obj = malloc(sizeof(t_object));
	if (!new_obj)
	{
		free(object);
		exit(1);
	}
	new_obj->object = object;
	new_obj->file_type = file_type;
	new_obj->next = NULL;
	if (!scene->object)
	{
		scene->object = new_obj;
		new_obj->id = 1;
		return ;
	}
	old_obj = scene->object;
	while (old_obj->next)
		old_obj = old_obj->next;
	old_obj->next = new_obj;
	new_obj->id = old_obj->id + 1;
	printf("id %d\n", new_obj->id);
}
