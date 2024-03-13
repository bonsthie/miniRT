#include "libft.h"
#include "mlx.h"
#include "scene_elements.h"
#include <fcntl.h>

static t_list *parse_line_by_line(int fd)
{
	t_list *list;
	t_list *last;
	t_list *new;
	char *line;

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
		ft_lstadd_back(&last, new);		
		if (!list)
			list = last;
		else 
			last = last->next;
		line = get_next_line(fd);
	}
	return (list);
}

void fill_mesh(t_mesh *mesh, char *file_name, t_list *file_ll)
{

}

void fill_obj(int fd, t_mesh *mesh, char *file_name)
{
	t_list *file_ll;

	file_ll = parse_line_by_line(fd);
	fill_mesh(&mesh, file_name, file_ll);
	ft_lstclear(&file_ll, free);
}

void fill_obj_texture(t_texture *texture, const char *texture_file)
{
	(void)texture;
	(void)texture_file;
}

t_object *parse_obj(const char *name, const char *texture)
{
	t_object *new_obj;
	int	fd;

	fd = open(name, O_RDONLY);
	if (fd < 0)
		return (NULL);
	new_obj = ft_calloc(1, sizeof(t_object));
	if (!new_obj)
	{
		close(fd);
		return (NULL);
	}
	fill_obj(fd, &new_obj->mesh, new_obj->file_name);
	new_obj->file_type = FILE_TYPE_OBJ;
	fill_obj_texture(&new_obj->texture, texture);
	return (new_obj);
}
