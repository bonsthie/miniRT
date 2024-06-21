/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_scene.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yroussea <yroussea@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 13:14:19 by yroussea          #+#    #+#             */
/*   Updated: 2024/06/21 13:32:19 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_driver.h"
#include "rt_mesh_obj.h"
#include <rt_math.h>
#include <rt_scene_elements.h>
#include <stdbool.h>

t_v4f get_screen_center(void)
{
    return ((t_v4f){RT_WIDTH / 2.0f, RT_HEIGHT / 2.0f, 100.0f, 1.0f});
}

void	create_rotation_tr_matrix(t_v4f *tr, t_rotation rotate, t_v4f offset)
{
	rotate_pitch(rotate, tr);
	rotate_yaw(rotate, tr);
	rotate_roll(rotate, tr);
	tr[0][3] = offset[0];
	tr[1][3] = offset[1];
	tr[2][3] = offset[2];
}

void	rotate_center(t_v4f *tr, t_v4f *vertex)
{
	t_v4f tmp = *vertex - get_screen_center();
	tmp[3] = 1;
	matrix_multiplication1x4(tr, tmp, &tmp);
	*vertex = tmp + get_screen_center();
}

// void	test_center(t_v4f *tr, t_offset *off)
// {
// 	t_v4f tmp = (t_v4f){off->x, off->y, off->z, 0} - get_screen_center();
// 	matrix_multiplication1x4(tr, tmp, &tmp);
// 	tmp += get_screen_center();
// 	// printf("%f %f %f\n", off->x, off->y, off->z);
// }

void	update_single_object(t_object_mesh *object, t_v4f *tr)
{
	#pragma omp parallel for
	for (size_t i = 0; i < object->mesh.size_mesh.vertex; i++)
		rotate_center(tr, &object->mesh.vertex[i].v4f);
	// test_center(tr, object->offset);
}

void	find_offset(t_v4f *cam, t_rotation lambda)
{
	t_v4f				tr[4];
	tr[0] = (t_v4f){1, 0, 0, 0};
	tr[1] = (t_v4f){0, 1, 0, 0};
	tr[2] = (t_v4f){0, 0, 1, 0};
	tr[3] = (t_v4f){0, 0, 0, 1};
	create_rotation_tr_matrix(tr, lambda, (t_v4f){0, 0, 0, 1});
	matrix_multiplication1x4(tr, *cam, cam);
}


/*
	*permet de sauvegarder l etat initiale de l'object,
	a mettre dans struct
*/
void	save_vec(bool bo, t_object *obj)
{
	static t_v4f	*save = NULL;
	t_object_mesh	*object;

	if (bo == 0)
	{
		object = obj->object;
		for (size_t i = 0; i < object->mesh.size_mesh.vertex; i++)
		{
			object->mesh.vertex[i].v4f = save[i] ;
		}
		return ;
	}
	if (bo == 1 && save == NULL)
	{
		object = obj->object;
		save = malloc(sizeof(t_v4f) * object->mesh.size_mesh.vertex);
		for (size_t i = 0; i < object->mesh.size_mesh.vertex; i++)
		{
			save[i] = object->mesh.vertex[i].v4f;
		}
	}
}

void	update_scene(t_object *object, t_rotation lambda, t_camera *cam)
{
	t_v4f				tr[4];
	static t_v4f		init_cam = (t_v4f){RT_WIDTH / 2, RT_HEIGHT /2, -100, 0};
	static t_rotation	all_lambda = (t_rotation){0, 0, 0};
	t_v4f				offset = init_cam - cam->coord;

	all_lambda = (t_rotation){lambda.pitch + all_lambda.pitch,
		lambda.yaw + all_lambda.yaw, lambda.roll + all_lambda.roll};
	find_offset(&offset, all_lambda);
	tr[0] = (t_v4f){1, 0, 0, 0};
	tr[1] = (t_v4f){0, 1, 0, 0};
	tr[2] = (t_v4f){0, 0, 1, 0};
	tr[3] = (t_v4f){0, 0, 0, 1};
	create_rotation_tr_matrix(tr, all_lambda, offset);
	save_vec(1, object); // doit aussi etre actualiser si obj rot/bouge
	save_vec(0, object);
	while (object)
	{
		update_single_object(object->object, tr);
		object = object->next;
	}
}
