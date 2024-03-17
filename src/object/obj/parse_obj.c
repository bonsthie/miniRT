#include "libft.h"
#include "mesh_obj.h"
#include "obj_intern.h"
#include "scene_elements.h"
#include <fcntl.h>
#include <stdio.h>

void update_mesh_count(char *line, t_size_mesh *size_mesh)
{
	if (!ft_strncmp(line, "v ", 2))
		size_mesh->vertex++;
	else if (!ft_strncmp(line, "vn ", 3))
		size_mesh->normal++;
	else if (!ft_strncmp(line, "vt ", 3))
		size_mesh->texture++;
	else if (!ft_strncmp(line, "f ", 2))
		size_mesh->face++;
}

static t_list	*parse_line_by_line(int fd, t_size_mesh *size_mesh)
{
	t_list	*list;
	t_list	*last;
	t_list	*new;
	char	*line;

	list = NULL;
	last = NULL;
	line = get_next_line(fd);
	while (line)
	{
		new = ft_lstnew(line);
		if (!new)
		{
			free(line);
			ft_lstclear(&list, free);
			return (NULL);
		}
		update_mesh_count(line, size_mesh);
		ft_lstadd_back(&last, new);
		if (!list)
			list = last;
		else
			last = last->next;
		line = get_next_line(fd);
	}
	return (list);
}

int	fill_mesh(t_mesh *mesh, char *file_name, t_list *file_ll)
{
	printf("vertex %ld normal %ld texture %ld face %ld\n", mesh->size_mesh.vertex, mesh->size_mesh.normal, mesh->size_mesh.texture, mesh->size_mesh.face);
	if (alloc_mesh(mesh))
		return (1);
	while (file_ll)
	{
		if (!file_name && !ft_strncmp("o ", file_ll->content, 2))
			file_name = ft_strdup(file_ll->content + 2);
		if (!ft_strncmp("v ", file_ll->content, 2))
			break;
		file_ll = file_ll->next;
	}
	fill_vertex(mesh->vertex, mesh->size_mesh.vertex, &file_ll);
	fill_texture(mesh->texture_coord, mesh->size_mesh.texture, &file_ll);
	fill_normal(mesh->normal, mesh->size_mesh.normal, &file_ll);
	fill_face(mesh->face, mesh->size_mesh.face, &file_ll);
	printf("end\n");
	return (0);
}

void	fill_obj(int fd, t_mesh *mesh, char *file_name)
{
	t_list	*file_ll;
	int		error;

	printf("vertex %ld normal %ld texture %ld face %ld\n", mesh->size_mesh.vertex, mesh->size_mesh.normal, mesh->size_mesh.texture, mesh->size_mesh.face);
	ft_bzero(&mesh->size_mesh, sizeof(t_size_mesh));
	file_ll = parse_line_by_line(fd, &mesh->size_mesh);
	if (!file_ll)
	{
		ft_putstr_fd("Error : [malloc faild in the file parsing]", 2);
		return ;
	}
	error = fill_mesh(mesh, file_name, file_ll);
	ft_lstclear(&file_ll, free);
	if (error == 1)
		ft_putstr_fd("Error : [malloc faild in the mesh creation]", 2);
}

void	fill_obj_texture(t_texture *texture, const char *texture_file)
{
	(void)texture;
	(void)texture_file;
}

t_object_mesh	*parse_obj(const char *name, const char *texture)
{
	t_object_mesh	*new_obj;
	int			fd;

	fd = open(name, O_RDONLY);
	if (fd < 0)
		return (NULL);
	new_obj = ft_calloc(1, sizeof(t_object_mesh));
	if (!new_obj)
	{
		close(fd);
		return (NULL);
	}
	fill_obj(fd, &new_obj->mesh, new_obj->file_name);
	fill_obj_texture(&new_obj->texture, texture);
	close(fd);
	return (new_obj);
}
