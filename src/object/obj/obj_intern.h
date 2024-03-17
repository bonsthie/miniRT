/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_intern.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 13:39:58 by babonnet          #+#    #+#             */
/*   Updated: 2024/03/17 00:54:22 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJ_INTERN_H
#define OBJ_INTERN_H

#include "mesh_obj.h"
#include "libft.h"

void free_mesh(t_mesh *mesh);
int alloc_mesh(t_mesh *mesh);


void fill_vertex(t_v4f *vertex, size_t size, t_list **file_ll);
void fill_normal(t_v4f *vertex, size_t size, t_list **file_ll);
void fill_texture(t_texture_coord *texture_coord, size_t size, t_list **file_ll);
void fill_face(t_face *face, size_t size, t_list **file_ll);

#endif
