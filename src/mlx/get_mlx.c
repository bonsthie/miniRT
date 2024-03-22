/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_mlx.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 13:25:11 by babonnet          #+#    #+#             */
/*   Updated: 2024/03/22 15:47:29 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_data.h"
#include <stdlib.h>

t_mlx	*get_mlx(void)
{
	static t_mlx	mlx = {.mouse_x = -1, .mouse_y = -1, .image = NULL,
			.connection = NULL, .window = NULL};

	return (&mlx);
}
