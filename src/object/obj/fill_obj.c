/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_obj.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 20:32:56 by babonnet          #+#    #+#             */
/*   Updated: 2024/03/18 20:04:56 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mesh_obj.h"
#include "miniRT.h"
#include "libft.h"
#include <stddef.h>
#include <stdio.h>

void fill_vertex(t_v4f *vertex, size_t size, t_list **file_ll)
{
	char *str;

	while (size--)
	{
		str = (*file_ll)->content;
		str++;
		//printf("%s", str);
		(*vertex)[0] = ft_strtod(str, &str);
		//printf("%f\n", (*vertex)[0]);
		(*vertex)[1] = ft_strtod(str, &str);
		//printf("%f\n", (*vertex)[1]);
		(*vertex)[2] = ft_strtod(str, &str);
		//printf("%f\n", (*vertex)[2]);
		(*vertex)[3] = 1;
		vertex++;
		*file_ll = (*file_ll)->next;
	}
}

void fill_normal(t_v4f *vertex, size_t size, t_list **file_ll)
{
	char *str;

	while (size--)
	{
		str = (*file_ll)->content;
		str += 2;
		//printf("%s", str);
		(*vertex)[0] = ft_strtod(str, &str);
		//printf("%f\n", (*vertex)[0]);
		(*vertex)[1] = ft_strtod(str, &str);
		//printf("%f\n", (*vertex)[1]);
		(*vertex)[2] = ft_strtod(str, &str);
		//printf("%f\n", (*vertex)[2]);
		(*vertex)[3] = 1;
		vertex++;
		*file_ll = (*file_ll)->next;
	}
}

void fill_texture(t_texture_coord *texture_coord, size_t size, t_list **file_ll)
{
	char *str;

	while (size--)
	{
		str = (*file_ll)->content;
		str += 2;
		texture_coord->u = ft_strtod(str, &str);
		texture_coord->v = ft_strtod(str, &str);
		texture_coord++;
		*file_ll = (*file_ll)->next;
	}
}

static size_t count_face(char *str)
{
	char **strs;
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

int fill_face(t_face *face, size_t size, t_list **file_ll)
{
	char *str;
	size_t		i;

	while (size-- && *file_ll)
	{
		str = (*file_ll)->content;
		str++;
		printf("%s", str);
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
				face->point[i].vertex = strtol(str, &str, 10);
				str++;
				face->point[i].texture = strtol(str, &str, 10);
				str++;
				face->point[i].normal = strtol(str, &str, 10);
				printf(" %ld/%ld/%ld", face->point[i].vertex, face->point[i].texture, face->point[i].normal);
				i++;
			}
			printf("\n");
		}
		face++;
		*file_ll = (*file_ll)->next;
	}
	return (0);
}
