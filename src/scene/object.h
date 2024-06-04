/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 15:56:38 by babonnet          #+#    #+#             */
/*   Updated: 2024/06/03 21:16:23 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECT_H
#define OBJECT_H

#include "rt_driver.h"
#include <miniRT.h>
#include <rt_scene_elements.h>

void add_object(t_scene *scene, void *object, t_file_type file_type);
t_object_mesh	*parse_obj(const char *name, const char *texture);
void	print_obj(t_object_mesh *object, t_img *img);

#endif
