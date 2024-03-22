/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 13:17:57 by babonnet          #+#    #+#             */
/*   Updated: 2024/03/22 15:47:29 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "mlx.h"
#include "mlx_data.h"

t_mlx	*init_mlx_data(void)
{
	t_mlx	*mlx;

	mlx = get_mlx();
	mlx->connection = mlx_init();
	if (!mlx->connection)
		exit_message(1, "Error : [MacroLibx connection faild]");
	mlx->window = mlx_new_window(mlx->connection, WIDTH, HEIGHT, "miniRT");
	if (!mlx->window)
		exit_message(1, "Error : [MacroLibx window creation faild]");
	return (mlx);
}
