/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_obj.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 20:32:56 by babonnet          #+#    #+#             */
/*   Updated: 2024/08/19 16:24:36 by bonsthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "miniRT.h"
#include <rt_mesh_obj.h>
#include <stddef.h>
#include <stdio.h>

void	fill_vertex(t_vec3 *vertex, size_t size, t_list **file_ll)
{
	static size_t	total_size = 0;
	char			*str;

	str = (*file_ll)->content;
	vertex += total_size;
	while (total_size < size && *file_ll && !ft_strncmp(str, "v ", 2))
	{
		str++;
		(*vertex).x = ft_strtod(str, &str);
		(*vertex).y = ft_strtod(str, &str);
		(*vertex).z = ft_strtod(str, &str);
		(*vertex).w = 1;
		vertex++;
		total_size++;
		if (*file_ll)
			*file_ll = (*file_ll)->next;
		str = (*file_ll)->content;
	}
	if (total_size == size)
		total_size = 0;
}

void	fill_normal(t_vec3 *vertex, size_t size, t_list **file_ll)
{
	static size_t	total_size = 0;
	char			*str;

	str = (*file_ll)->content;
	vertex += total_size;
	while (total_size < size && *file_ll && !ft_strncmp(str, "vn ", 3))
	{
		str += 2;
		(*vertex).x = ft_strtod(str, &str);
		(*vertex).y = ft_strtod(str, &str);
		(*vertex).z = ft_strtod(str, &str);
		(*vertex).w = 1;
		vertex++;
		total_size++;
		if (*file_ll)
			*file_ll = (*file_ll)->next;
		str = (*file_ll)->content;
	}
	if (total_size == size)
		total_size = 0;
}

void	fill_texture(t_texture_coord *texture_coord, size_t size,
		t_list **file_ll)
{
	static size_t	total_size = 0;
	char			*str;

	str = (*file_ll)->content;
	texture_coord += total_size;
	while (total_size < size && *file_ll && !ft_strncmp(str, "vt ", 3))
	{
		str += 2;
		texture_coord->u = ft_strtod(str, &str);
		texture_coord->v = ft_strtod(str, &str);
		texture_coord++;
		*file_ll = (*file_ll)->next;
		if (*file_ll)
			str = (*file_ll)->content;
		total_size++;
	}
	if (total_size == size)
		total_size = 0;
}

size_t	count_face(char *str)
{
	char	**strs;
	size_t	i;

	if (!str)
		return (0);
	strs = ft_split(str, ' ');
	i = 0;
	while (strs[i] && ft_isdigit(*strs[i]) && ft_strncmp(strs[i], "0x", 2))
		i++;
	free_strs(strs);
	return (i);
}

void	parse_face(t_face *face, char **str, int i)
{
	/* yoooo remove it  strtol illegal type shit */
	face->point[i].vertex = strtol(*str, str, 10) - 1;
	if (**str != '/')
		return ;
	(*str)++;
	face->point[i].texture = strtol(*str, str, 10) - 1;
	if (**str != '/')
		return ;
	(*str)++;
	face->point[i].normal = strtol(*str, str, 10) - 1;
}

int	fill_face(t_face *face, size_t size, t_list **file_ll)
{
	static size_t	total_size = 0;
	char			*str;
	size_t			i;

	str = (*file_ll)->content;
	face += total_size;
	while (total_size < size && *file_ll && !ft_strncmp(str, "f ", 2))
	{
		str++;
		/* printf("%s", str); */
		face->count = count_face(str);
		if (!face->count)
			face->point = NULL;
		else
		{
			face->point = malloc(face->count * sizeof(t_point));
			if (!face->point)
			{
				free(face->point);
				return (1);
			}
			i = 0;
			while (i < face->count)
			{
				// need to change strtol
				parse_face(face, &str, i);
				i++;
			}
		}
		face->color.value = 0xFFFFFFFF;
		face++;
		*file_ll = (*file_ll)->next;
		if (*file_ll)
			str = (*file_ll)->content;
		total_size++;
	}
	if (total_size == size)
		total_size = 0;
	return (0);
}
