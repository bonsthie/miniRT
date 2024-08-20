/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 22:08:36 by babonnet          #+#    #+#             */
/*   Updated: 2024/08/20 18:24:13 by bonsthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_driver.h"
#include "miniRT.h"
#include "_hook.h"
#include "rt_scene_elements.h"

void hook_creation(t_screen *screen, struct s_hook_data *data)
{
	t_loop *loop;

	loop = &data->scene->loop;
	rt_on_event(screen, RT_KEYUP, &loop->hook.keyup, data);
	rt_on_event(screen, RT_MOUSEDOWN, &loop->hook.mousedown, data);
	rt_on_event(screen, RT_MOUSEWHEEL, &loop->hook.mousewheel, data);
	rt_on_event(screen, RT_MOUSEUP, &loop->hook.mouseup, data);
}
