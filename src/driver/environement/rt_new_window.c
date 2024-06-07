/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_new_window.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 15:22:18 by babonnet          #+#    #+#             */
/*   Updated: 2024/06/07 15:35:30 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "../_rt_mlx.h"

void *rt_new_window(t_screen *screen)
{
	return (mlx_new_window(screen->mlx, 100, 30, "test"));
}
