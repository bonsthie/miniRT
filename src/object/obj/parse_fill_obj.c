/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_fill_obj.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 12:35:58 by babonnet          #+#    #+#             */
/*   Updated: 2024/03/22 15:47:29 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "mesh_obj.h"

static void	update_mesh_count(char *line, t_size_mesh *size_mesh)
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

t_list	*parse_line_by_line(int fd, t_size_mesh *size_mesh)
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
