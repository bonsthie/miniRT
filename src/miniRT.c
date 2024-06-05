/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 18:58:46 by babonnet          #+#    #+#             */
/*   Updated: 2024/06/05 17:11:51 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt_driver.h>
#include <rt_mesh_obj.h>
#include <rt_scene_elements.h>

#include "scene/object.h"

int loop(t_scene *scene, t_img *img, t_screen *screen)
{
	t_object_mesh *obj = scene->object->object;
	print_obj_to_image(obj, img);
	obj->new_rotation.yaw = 1;
	update_size_obj(obj);
	rt_print_img_screen(img, screen, 0, 0);
	return (0);
}

void non(void *non)
{
	(void)non;
}

int main(int ac, char **av)
{
	t_scene scene;
	t_screen	*screen;

	screen = rt_init();
	if (!screen)
		return (1);
	rt_add_text_button_top(screen, "yoo", NULL, non);
	rt_add_text_button_top(screen, "comment", NULL, non);
	rt_add_text_button_top(screen, "ca", NULL, non);
	rt_add_text_button_top(screen, "va", NULL, non);
	scene.object = NULL;
	add_object(&scene, parse_obj(av[1], NULL), OBJECT_OBJ);
	(void)av;
	(void)ac;
	rt_loop(&scene, screen, loop);
	rt_destroy(screen);
}
