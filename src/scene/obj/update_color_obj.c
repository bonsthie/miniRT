/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_color_obj.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 15:30:11 by babonnet          #+#    #+#             */
/*   Updated: 2024/08/19 16:24:36 by bonsthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_mesh_obj.h"

void	update_color_object(t_object_mesh *object, int new_color)
{
	size_t	i;

	i = 0;
	while (i < object->mesh.size_mesh.face)
	{
		object->mesh.face[i].color.value = new_color;
		i++;
	}
}
