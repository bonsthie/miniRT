/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bonsthie <bonsthie@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 16:24:33 by bonsthie          #+#    #+#             */
/*   Updated: 2024/08/29 14:20:27 by bonsthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "obj_intern.h"
#include "parse.h"
#include "rt_driver.h"
#include <fcntl.h>
#include <rt_mesh_obj.h>
#include <stdio.h>

void	fill_mesh(t_mesh *mesh, char **file_name, t_list *file_ll)
{
	int	error;

	error = 0;
	printf("vertex %ld normal %ld texture %ld face %ld\n",
		mesh->size_mesh.vertex, mesh->size_mesh.normal, mesh->size_mesh.texture,
		mesh->size_mesh.face);
	if (alloc_mesh(mesh))
		exit_message(1, "Error : [malloc failed in the mesh creation]\n");
	while (file_ll)
	{
		if (!*file_name && !ft_strncmp("o ", file_ll->content, 2))
			*file_name = ft_strdup(file_ll->content + 2);
		else if (!ft_strncmp(file_ll->content, "v ", 2))
			fill_vertex(&mesh->vertex->vec3, mesh->size_mesh.vertex, &file_ll);
		else if (!ft_strncmp(file_ll->content, "vn ", 3))
			fill_normal(&mesh->normal->vec3, mesh->size_mesh.normal, &file_ll);
		else if (!ft_strncmp(file_ll->content, "vt ", 3))
			fill_texture(mesh->texture_coord, mesh->size_mesh.texture,
				&file_ll);
		else if (!ft_strncmp(file_ll->content, "f ", 2))
			error = fill_face(mesh->face, mesh->size_mesh.face, &file_ll);
		else if (file_ll)
			file_ll = file_ll->next;
		if (error)
			exit_message(1, "Error : [malloc failed in the mesh creation]\n");
	}
}

void	fill_obj(int fd, t_object_mesh *object)
{
	t_mesh	*mesh;

	mesh = &object->mesh;
	printf("vertex %ld normal %ld texture %ld face %ld\n",
		mesh->size_mesh.vertex, mesh->size_mesh.normal, mesh->size_mesh.texture,
		mesh->size_mesh.face);
	ft_bzero(&mesh->size_mesh, sizeof(t_size_mesh));
	object->metadata.file = parse_line_by_line(fd, &mesh->size_mesh);
	if (!object->metadata.file)
		exit_message(1,
			"Error : [malloc failed in the metadata.file parsing]\n");
	fill_mesh(mesh, &object->metadata.file_name, object->metadata.file);
	ft_lstclear(&object->metadata.file, free);
}

void	fill_obj_texture(t_texture *texture, const char *texture_file)
{
	(void)texture;
	(void)texture_file;
}

void	save_vec(t_object_mesh *object)
{
	size_t	i;

	i = 0;
	while (i < object->mesh.size_mesh.vertex)
	{
		object->mesh.vertex_init[i] = object->mesh.vertex[i].v4f;
		i++;
	}
}

t_object_mesh	*parse_obj(const char *name, const char *texture)
{
	t_object_mesh	*new_obj;

	new_obj = ft_calloc(1, sizeof(t_object_mesh));
	if (!new_obj)
		rt_error_window("Error : [malloc fild in the creation of a new object]\n");
	new_obj->metadata.fd = open(name, O_RDONLY);
	if (new_obj->metadata.fd < 0)
	{
		exit_message(1, "Error : [cannot open the .obj metadata.file]\n");
	}
	fill_obj(new_obj->metadata.fd, new_obj);
	fill_obj_texture(&new_obj->texture, texture);
	close(new_obj->metadata.fd);
	new_obj->new_scale = 10;
	new_obj->new_rotation.pitch = 90;
	new_obj->new_rotation.yaw = 0;
	new_obj->new_rotation.roll = 0;
	new_obj->new_offset.x = 0;
	new_obj->new_offset.y = 0;
	new_obj->new_offset.z = 0;
	find_center(new_obj, &new_obj->mesh.vertex->v4f, &new_obj->center.v4f);
	save_vec(new_obj);
	return (new_obj);
}

/* t_object_mesh	*parse_model(const char *name, const char *texture) */
/* { */
/* 	t_object_mesh	*new_obj; */
/*  */
/*  */
/* 	new_obj = ft_calloc(1, sizeof(t_object_mesh)); */
/* 	if (!new_obj) */
/* 	{ */
/* 		rt_error_window("Error : [malloc fild in the creation of a new object]\n"); */
/*  */
/* 	} */
/*  */
/* } */
