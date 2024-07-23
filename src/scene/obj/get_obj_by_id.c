/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_obj_by_id.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 00:30:06 by babonnet          #+#    #+#             */
/*   Updated: 2024/07/23 13:58:31 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_scene_elements.h"
#include <stdio.h>

t_object *get_obj_by_id(t_object *object, short id)
{
	while(object)
	{
		if (object->id == id)
		{
			// printf("%d  %d\n", object->id, id);
			return (object);
		}
		object = object->next;
	}
	return (NULL);
}
