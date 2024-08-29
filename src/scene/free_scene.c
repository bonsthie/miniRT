/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bonsthie <bonsthie@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 14:13:03 by bonsthie          #+#    #+#             */
/*   Updated: 2024/08/29 15:42:09 by bonsthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "rt_scene_elements.h"
#include "rt_mesh_obj.h"

void	free_mesh(t_mesh *mesh)
{
	size_t i;

	if (mesh->vertex_init)
		free(mesh->vertex_init);
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
}

void free_object_metadata(struct s_object_metadata *metadata)
{
	close (metadata->fd);
	if (metadata->file_name)
		free(metadata->file_name);
	ft_lstclear(&metadata->file, free);
}

void	free_object_mesh(t_object_mesh *object)
{
	free_mesh(&object->mesh);
	free_object_metadata(&object->metadata);
}

void	free_object(t_object *object)
{
	t_object *next;

	while (object)
	{
		if (object->object)
		{
			if (object->file_type == OBJECT_OBJ)
				free_object_mesh(object->object);
			free(object->object);
		}
		next = object->next;
		free(object);
		object = next;
	}
	object = NULL;
}

void free_scene_asset(t_asset *asset)
{
	if (!asset)
		return ;
	if (asset->gizmo_img)
		free(asset->gizmo_img);
	if (asset->gizmo_scale)
		free_object_mesh(asset->gizmo_scale);
	free(asset->gizmo_scale);
	if (asset->gizmo_rotate)
		free_object_mesh(asset->gizmo_rotate);
	free(asset->gizmo_rotate);
	if (asset->gizmo_translate)
		free_object_mesh(asset->gizmo_translate);
	free(asset->gizmo_translate);
}
