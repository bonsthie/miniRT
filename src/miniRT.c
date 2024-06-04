/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 18:58:46 by babonnet          #+#    #+#             */
/*   Updated: 2024/06/04 13:33:48 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt_driver.h>
#include <miniRT.h>
#include <stdio.h>

#include "scene/object.h"
#include "rt_mesh_obj.h"
#include "rt_scene_elements.h"

int loop(t_scene *scene, t_img *img)
{
	(void)scene;
	t_object_mesh *obj = scene->object->object;

	print_obj(obj, img);

	obj->new_rotation.yaw = 1;
	update_size_obj(obj);
	return (0);
}

int main(int ac, char **av)
{
	t_scene scene;
	
	scene.object = NULL;
	add_object(&scene, parse_obj(av[1], NULL), OBJECT_OBJ);
	(void)av;
	(void)ac;
	rt_loop(&scene, loop);
}
