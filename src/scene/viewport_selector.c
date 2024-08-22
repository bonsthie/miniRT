/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   viewport_selector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bonsthie <bonsthie@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 13:02:31 by bonsthie          #+#    #+#             */
/*   Updated: 2024/08/22 14:44:04 by bonsthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_scene_elements.h"
#include "raytracer.h"
#include "editor.h"
#include "../hook/_hook.h"
#include <stdio.h>

void	select_viewport_raytracer(void *data)
{
	t_loop *loop;

	loop = &((t_scene *)data)->loop;
	loop->hook.keyup = NULL,
	loop->hook.keydown = NULL,
	loop->hook.mouseup = NULL,
	loop->hook.mousedown = NULL,
	loop->hook.mousewheel = NULL;
	loop->f = raytracer;
}

void	select_viewport_editor(void *data)
{
	t_loop *loop;

	loop = &((t_scene *)data)->loop;
	loop->hook.keyup = &keyup_hook_editor,
	loop->hook.keydown = NULL,
	loop->hook.mouseup = &mouseup_hook_editor,
	loop->hook.mousedown = &mousedown_hook_editor,
	loop->hook.mousewheel = &mousewheel_hook_editor;
	loop->f = editor;
}
