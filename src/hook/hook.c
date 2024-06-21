/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 22:08:36 by babonnet          #+#    #+#             */
/*   Updated: 2024/06/21 09:33:55 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_driver.h"
#include "miniRT.h"
#include "_hook.h"

void hook_creation(t_screen *screen, struct s_hook_data *data)
{
	rt_on_event(screen, RT_KEYUP, keyup_hook, data);
	rt_on_event(screen, RT_MOUSEDOWN, mousedown_hook, data);
}
