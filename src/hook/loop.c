/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 17:53:49 by babonnet          #+#    #+#             */
/*   Updated: 2024/03/24 18:14:09 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mesh_obj.h"
#include "miniRT.h"
#include "mlx.h"
#include "print.h"
#include "scene_elements.h"

int loop(void *data)
{
	t_object *object;
	t_mlx *mlx = get_mlx();

	object = get_scene()->object;
	t_object_mesh *obj = object->object;
	obj->rotation.yaw++;
	update_size_obj(object->object);
	print_obj(object->object, mlx);
	sleep(3);
	if (mlx->image)
		mlx_destroy_image(mlx->connection, mlx->image);
	(void)data;
	return (0);
}
