/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 23:35:03 by babonnet          #+#    #+#             */
/*   Updated: 2024/08/19 16:24:36 by bonsthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "libft.h"
# include "rt_mesh_obj.h"

t_list	*parse_line_by_line(int fd, t_size_mesh *size_mesh);

void	fill_vertex(t_vec3 *vertex, size_t size, t_list **file_ll);
void	fill_normal(t_vec3 *vertex, size_t size, t_list **file_ll);
int		fill_face(t_face *face, size_t size, t_list **file_ll);
void	fill_texture(t_texture_coord *texture_coord, size_t size,
			t_list **file_ll);

void	fill_obj_texture(t_texture *texture, const char *texture_file);
void	fill_obj(int fd, t_object_mesh *object);

size_t	count_face(char *str);
void	parse_face(t_face *face, char **str, int i);
void	save_vec(t_object_mesh *object);

#endif // PARSE_H
