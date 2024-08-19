/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   viewport_selector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bonsthie <bonsthie@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 13:02:31 by bonsthie          #+#    #+#             */
/*   Updated: 2024/08/19 13:13:24 by bonsthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_scene_elements.h"
#include <stdio.h>

void select_viewport_raytracer(void *data)
{
	printf("raytracer\n");
	((t_status *)data)->viewport_status = VP_RAYTRACER;
}

void select_viewport_editor(void *data)
{
	printf("editor\n");
	((t_status *)data)->viewport_status = VP_EDITOR;
}
