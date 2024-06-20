/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 18:16:34 by babonnet          #+#    #+#             */
/*   Updated: 2024/06/20 18:17:34 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECT_H
#define OBJECT_H

#include "rt_driver.h"
#include <miniRT.h>
#include <rt_scene_elements.h>

void add_object(t_scene *scene, void *object, t_file_type file_type);
t_object_mesh	*parse_obj(const char *name, const char *texture);
void	print_obj_to_image(t_object_mesh *object, t_img *img, int id);
void update_color_object(t_object_mesh *object, int new_color);

#endif
