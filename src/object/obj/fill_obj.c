/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_obj.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 20:32:56 by babonnet          #+#    #+#             */
/*   Updated: 2024/03/17 01:23:13 by babonnet         ###   ########.fr       */
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

	while(ft_strncmp("v ", (*file_ll)->content, 2))
		*file_ll = (*file_ll)->next;
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

	while(ft_strncmp("vn ", (*file_ll)->content, 3))
		*file_ll = (*file_ll)->next;
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

	while(ft_strncmp("vt ", (*file_ll)->content, 3))
		*file_ll = (*file_ll)->next;
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

void fill_face(t_face *face, size_t size, t_list **file_ll)
{
	char *str;

	while(ft_strncmp("f ", (*file_ll)->content, 2))
		*file_ll = (*file_ll)->next;
	while (size--)
	{
		str = (*file_ll)->content;
		//printf("%s", str);
		str++;
		face->point1.vertex = strtol(str, &str, 10);
		// need to change ft_strtol
		str++;
		face->point1.texture = strtol(str, &str, 10);
		str++;
		face->point1.normal = strtol(str, &str, 10);
		face->point2.vertex = strtol(str, &str, 10);
		str++;
		face->point2.texture = strtol(str, &str, 10);
		str++;
		face->point2.normal = strtol(str, &str, 10);
		face->point3.vertex = strtol(str, &str, 10);
		str++;
		face->point3.texture = strtol(str, &str, 10);
		str++;
		face->point3.normal = strtol(str, &str, 10);
		//printf("f %ld/%ld/%ld %ld/%ld/%ld %ld/%ld/%ld\n", face->point1.vertex, face->point1.texture, face->point1.normal, face->point2.vertex, face->point2.texture, face->point2.normal, face->point3.vertex, face->point3.texture, face->point3.normal);
		face++;
		*file_ll = (*file_ll)->next;
	}
	printf("%ld\n", size);
}
