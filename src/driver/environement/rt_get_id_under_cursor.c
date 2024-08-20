/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_get_id_under_cursor.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 22:07:23 by babonnet          #+#    #+#             */
/*   Updated: 2024/08/20 12:26:21 by bonsthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../_rt_mlx.h"

short	rt_id_obj_under_curssor(t_screen *screen, t_img *img)
{
	return (img->obj_id[screen->mouse_y][screen->mouse_x]);
}
