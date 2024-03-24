/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 00:04:19 by babonnet          #+#    #+#             */
/*   Updated: 2024/03/24 18:14:55 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hook.h"
#include "mesh_obj.h"
#include "mlx.h"
#include "mlx_data.h"
#include "parsing_file.h"
#include "print.h"
#include "scene_elements.h"

int	main(__attribute_maybe_unused__ int ac,
		__attribute_maybe_unused__ char **av)
{
	t_mlx	*mlx;
	t_object *object;

	mlx = init_mlx_data();
	parse_obj(av[1], 0);
	object = get_scene()->object;
	(void)object;
	update_size_obj(object->object);
	print_obj(object->object, mlx);
	hook(mlx);
	//mlx_loop_hook(mlx->connection, loop, NULL);
	mlx_loop(mlx->connection);
	mlx_destroy_window(mlx->connection, mlx->window);
	mlx_destroy_image(mlx->connection, mlx->image);
	mlx_destroy_display(mlx->connection);
}
