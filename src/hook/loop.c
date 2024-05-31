/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 17:53:49 by babonnet          #+#    #+#             */
/*   Updated: 2024/05/31 20:45:08 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mesh_obj.h"
#include "miniRT.h"
#include "mlx.h"
#include "mlx_data.h"
#include "print.h"
#include "scene_elements.h"

int loop(void *data)
{
	t_object *object;
	t_mlx *mlx = data;
	int zbuffer[HEIGHT][WIDTH];
	for (int i = 0; i < HEIGHT; i++)
	{
		for (int j = 0; j < WIDTH; j++)
			zbuffer[i][j] = INT_MAX;
	}

	object = get_scene()->object;
	t_object_mesh *obj = object->object;
	update_size_obj(object->object);
	print_obj(object->object, mlx, zbuffer);
	obj->new_rotation.yaw = 1;
	/* obj->new_rotation.pitch = 1; */
	/* obj->new_rotation.roll = 1; */
	/* obj->new_offset.y = 1; */
	/* obj->new_offset.x = 20; */
	(void)data;
	return (0);
}
