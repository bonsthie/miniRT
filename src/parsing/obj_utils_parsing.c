/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_utils_parsing.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 19:49:33 by babonnet          #+#    #+#             */
/*   Updated: 2024/08/29 15:35:18 by bonsthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "rt_scene_elements.h"
#include <rt_driver.h>
#include <rt_mesh_obj.h>
#include <stdlib.h>

int	alloc_mesh(t_mesh *mesh)
{
	t_size_mesh	*size_mesh;

	size_mesh = &mesh->size_mesh;
	ft_printf("%d\n", size_mesh->vertex);
	mesh->vertex = malloc(size_mesh->vertex * sizeof(t_v4f));
	mesh->vertex_init = malloc(size_mesh->vertex * sizeof(t_v4f));
	mesh->normal = malloc(size_mesh->normal * sizeof(t_v4f));
	mesh->texture_coord = malloc(size_mesh->texture * sizeof(t_texture_coord));
	mesh->face = malloc(size_mesh->face * sizeof(t_face));
	if (!mesh->vertex || !mesh->normal || !mesh->texture_coord || !mesh->face
		|| !mesh->vertex_init)
	{
		free_mesh(mesh);
		return (1);
	}
	return (0);
}
