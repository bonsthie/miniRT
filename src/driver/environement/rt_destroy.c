/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_destroy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 11:37:27 by babonnet          #+#    #+#             */
/*   Updated: 2024/06/05 11:38:15 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../_rt_mlx.h"
#include <mlx.h>

void rt_destroy(t_rt *rt)
{
	mlx_clear_window(rt->mlx, rt->win);
	mlx_destroy_display(rt->mlx);
}
