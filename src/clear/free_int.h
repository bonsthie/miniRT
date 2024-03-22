/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_int.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 14:12:38 by babonnet          #+#    #+#             */
/*   Updated: 2024/03/19 14:16:00 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FREE_INT_H
#define FREE_INT_H

#include "scene_elements.h"

void free_cam(t_camera *cam);
void free_light(t_light *light);
void free_object(t_object *object);

#endif
