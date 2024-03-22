/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_intern.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 13:39:58 by babonnet          #+#    #+#             */
/*   Updated: 2024/03/22 10:18:20 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJ_INTERN_H
# define OBJ_INTERN_H

# include "libft.h"
# include "mesh_obj.h"

void	free_mesh(t_mesh *mesh);
int		alloc_mesh(t_mesh *mesh);

t_list	*parse_line_by_line(int fd, t_size_mesh *size_mesh);

void	fill_vertex(t_v4f *vertex, size_t size, t_list **file_ll);
void	fill_normal(t_v4f *vertex, size_t size, t_list **file_ll);
void	fill_texture(t_texture_coord *texture_coord, size_t size,
			t_list **file_ll);
int		fill_face(t_face *face, size_t size, t_list **file_ll);

#endif
