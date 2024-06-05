#include "libft.h"
#include <rt_mesh_obj.h>
#include "obj_intern.h"
#include <fcntl.h>
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
	object->file = parse_line_by_line(fd, &mesh->size_mesh);
	if (!object->file)
		exit_message(1, "Error : [malloc failed in the file parsing]\n");
	fill_mesh(mesh, &object->file_name, object->file);
	ft_lstclear(&object->file, free);
}

void	fill_obj_texture(t_texture *texture, const char *texture_file)
{
	(void)texture;
	(void)texture_file;
}

t_object_mesh	*parse_obj(const char *name, const char *texture)
{
	t_object_mesh	*new_obj;

	new_obj = ft_calloc(1, sizeof(t_object_mesh));
	if (!new_obj)
		exit_message(1,
			"Error : [malloc fild in the creation of a new object]\n");
	new_obj->fd = open(name, O_RDONLY);
	if (new_obj->fd < 0)
	{
		exit_message(1, "Error : [cannot open the .obj file]\n");
	}
	fill_obj(new_obj->fd, new_obj);
	fill_obj_texture(&new_obj->texture, texture);
	new_obj->new_scale = 1;
	new_obj->new_rotation.pitch = 180;
	new_obj->new_rotation.yaw = 0;
	new_obj->new_rotation.roll = 0;
	new_obj->new_offset.x = 800;
	new_obj->new_offset.y = 550;
	new_obj->new_offset.z = 1;
	close(new_obj->fd);
	return (new_obj);
}

