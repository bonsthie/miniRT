/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_hook_window.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 15:09:22 by babonnet          #+#    #+#             */
/*   Updated: 2024/06/20 23:11:48 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"

int	rt_window_hook(int event, void *param)
{
	if (event == 0)
		mlx_loop_end(param);
	return (0);
}
