/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_obj.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 20:32:56 by babonnet          #+#    #+#             */
/*   Updated: 2024/03/29 14:41:13 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "mesh_obj.h"
#include "miniRT.h"
#include <stddef.h>
#include <stdio.h>

void	fill_vertex(t_vec3 *vertex, size_t size, t_list **file_ll)
{
	char	*str;

	while (size-- && *file_ll)
	{
		str = (*file_ll)->content;
		str++;
		// printf("%s", str);
		(*vertex).x = ft_strtod(str, &str);
		// printf("%f\n", (*vertex)[0]);
		(*vertex).y = ft_strtod(str, &str);
		// printf("%f\n", (*vertex)[1]);
		(*vertex).z = ft_strtod(str, &str);
		// printf("%f\n", (*vertex)[2]);
		(*vertex).w = 1;
		vertex++;
		*file_ll = (*file_ll)->next;
	}
}

void	fill_normal(t_vec3 *vertex, size_t size, t_list **file_ll)
{
	char	*str;

	while (size-- && *file_ll)
	{
		str = (*file_ll)->content;
		str += 2;
		// printf("%s", str);
		(*vertex).x = ft_strtod(str, &str);
		// printf("%f\n", (*vertex)[0]);
		(*vertex).y = ft_strtod(str, &str);
		// printf("%f\n", (*vertex)[1]);
		(*vertex).z = ft_strtod(str, &str);
		// printf("%f\n", (*vertex)[2]);
		(*vertex).w = 1;
		vertex++;
		*file_ll = (*file_ll)->next;
	}
}

void	fill_texture(t_texture_coord *texture_coord, size_t size,
		t_list **file_ll)
{
	char	*str;

	while (size-- && *file_ll)
	{
		str = (*file_ll)->content;
		str += 2;
		texture_coord->u = ft_strtod(str, &str);
		texture_coord->v = ft_strtod(str, &str);
		texture_coord++;
		*file_ll = (*file_ll)->next;
	}
}

static size_t	count_face(char *str)
{
	char	**strs;
	size_t	i;

	if (!str)
		return (0);
	strs = ft_split(str, ' ');
	i = 0;
	while (strs[i])
		i++;
	free_strs(strs);
	return (i);
}

int	fill_face(t_face *face, size_t size, t_list **file_ll)
{
	char	*str;
	size_t	i;

	while (size-- && *file_ll)
	{
		str = (*file_ll)->content;
		str++;
		//printf("%s", str);
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
				face->point[i].vertex = strtol(str, &str, 10) - 1;
				str++;
				face->point[i].texture = strtol(str, &str, 10) - 1;
				str++;
				face->point[i].normal = strtol(str, &str, 10) - 1;
				i++;
			}
		}
		face++;
		*file_ll = (*file_ll)->next;
	}
	return (0);
}
