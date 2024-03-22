/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 00:04:19 by babonnet          #+#    #+#             */
/*   Updated: 2024/03/22 17:19:24 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hook.h"
#include "mlx.h"
#include "mlx_data.h"
#include "parsing_file.h"

int	main(__attribute_maybe_unused__ int ac,
		__attribute_maybe_unused__ char **av)
{
	t_mlx	*mlx;

	mlx = init_mlx_data();
	parse_obj(av[1], 0);
	hook(mlx);
	// mlx_loop_hook(mlx->connection, loop, map);
	mlx_loop(mlx->connection);
}
