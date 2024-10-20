/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 18:16:34 by babonnet          #+#    #+#             */
/*   Updated: 2024/07/25 00:51:41 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECT_H
# define OBJECT_H

# include "rt_driver.h"
# include <miniRT.h>
# include <rt_scene_elements.h>

void			save_vec(t_object_mesh *object);
void			add_object(t_scene *scene, void *object, t_file_type file_type);
t_object_mesh	*parse_obj(const char *name, const char *texture);
t_object_mesh	*parse_rta(const char *name, const char *texture);
void			print_obj_to_image(t_object_mesh *object, t_img *img, int id);
void			print_obj_to_image_color(t_object_mesh *object, t_img *img, int id, unsigned int color);
void			update_color_object(t_object_mesh *object, int new_color);

t_object *get_obj_by_id(t_object *object, short id);
void create_transformation_matrix(t_v4f *transformation, t_object_mesh *object, uint8_t settings);
void	rotate(t_v4f *tr, t_v4f *result, t_v4f center);

#endif
