/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_mouse_clic.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yroussea <yroussea@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 14:32:31 by yroussea          #+#    #+#             */
/*   Updated: 2024/06/20 16:16:31 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "_hook.h"
#include "mlx.h"
#include "rt_driver.h"
#include "rt_mesh_obj.h"

t_rotation	during_right_clic(bool up, void *data)
{
	static bool			active = 0;
	static t_int_vec4	pos;
	t_screen			*screen;
	t_rotation			rot;

	screen = data;
	if (up)
	{
		active = 1 - active;
		mlx_mouse_get_pos(screen->mlx, &pos.x, &pos.y);
		if (active)
			mlx_mouse_hide();
		else
			mlx_mouse_show();
		return ((t_rotation){0, 0, 0});
	}
	if (!active)
		return ((t_rotation){0, 0, 0});
	mlx_mouse_get_pos(screen->mlx, &pos.z, &pos.w);
	rot = (t_rotation){(float)(pos.w - pos.y)/RT_HEIGHT*360,
		(float)(pos.x - pos.z)/RT_WIDTH*360, 0};
	mlx_mouse_move(screen->mlx, screen->win, pos.x, pos.y);
	return (rot);
}
