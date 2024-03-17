/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing_obj.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 19:49:33 by babonnet          #+#    #+#             */
/*   Updated: 2024/03/17 00:55:44 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mesh_obj.h"
#include "libft.h"
#include "miniRT.h"
#include <stdlib.h>

void free_mesh(t_mesh *mesh)
{
	if (mesh->vertex)
		free(mesh->vertex);
	if (mesh->normal)
		free(mesh->normal);
	if (mesh->texture_coord)
		free(mesh->texture_coord);
	if (mesh->face)
		free(mesh->face);
	mesh = NULL;
}

int alloc_mesh(t_mesh *mesh)
{
	t_size_mesh *size_mesh;

	size_mesh = &mesh->size_mesh;
	ft_printf("%d\n" ,size_mesh->vertex);
	mesh->vertex = malloc(size_mesh->vertex * sizeof(t_v4f));
	mesh->normal = malloc(size_mesh->normal * sizeof(t_v4f));
	mesh->texture_coord = malloc(size_mesh->texture * sizeof(t_texture_coord));
	mesh->face = malloc(size_mesh->face * sizeof(t_face));
	if (!mesh->vertex || !mesh->normal || !mesh->texture_coord || !mesh->face)
	{
		free_mesh(mesh);
		return (1);
	}
	return (0);
}
