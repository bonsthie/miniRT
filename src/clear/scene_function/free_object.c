/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_object.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 14:12:22 by babonnet          #+#    #+#             */
/*   Updated: 2024/03/22 15:47:28 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mesh_obj.h"
#include "scene_elements.h"

void	free_obj(t_object_mesh *object)
{
	t_mesh	*mesh;
	size_t	i;

	if (object->file_name)
		free(object->file_name);
	mesh = &object->mesh;
	if (!mesh)
		return ;
	if (mesh->vertex)
		free(mesh->vertex);
	if (mesh->normal)
		free(mesh->normal);
	if (mesh->texture_coord)
		free(mesh->texture_coord);
	if (mesh->face)
	{
		i = 0;
		while (i < mesh->size_mesh.face)
			free(mesh->face[i++].point);
		free(mesh->face);
	}
	if (object->file)
		ft_lstclear(&object->file, free);
}

void	free_object(t_object *object)
{
	while (object)
	{
		if (object->object && object->file_type == OBJECT_OBJ)
			free_obj(object->object);
		if (object->object)
			free(object->object);
		free(object);
		object = NULL;
	}
	object = NULL;
}
