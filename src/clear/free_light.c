/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_light.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 14:11:18 by babonnet          #+#    #+#             */
/*   Updated: 2024/03/19 14:12:01 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene_elements.h"
#include <stdlib.h>

void free_light(t_light *light)
{
	t_light *light_next;

	while (light)
	{
		light_next = light->next;
		free(light);
		light = light_next;
	}
}
