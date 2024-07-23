/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 19:14:27 by babonnet          #+#    #+#             */
/*   Updated: 2024/07/23 13:48:37 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hook/_hook.h"
#include "miniRT.h"
#include "object.h"
#include <rt_driver.h>
#include <rt_mesh_obj.h>
#include <rt_scene_elements.h>
#include <stdio.h>
#include <string.h>


bool	init_hooks(t_scene *scene, t_img *img, t_screen *screen)
{
	static struct s_hook_data	data;

	data.scene = scene;
	data.screen = screen;
	data.img = img;
	hook_creation(screen, &data);
	return (false);
}

void loop_hooks(t_scene *scene, t_img *img, t_screen *screen)
{
	static bool		init_hooks_bool = true;
	static struct s_hook_data	hdata;

	hdata.scene = scene;
	hdata.screen = screen;
	hdata.img = img;
	if (init_hooks_bool == true)
		init_hooks_bool = init_hooks(scene, img, screen);
	if (scene->status.mouse_right_press)
		move_scene_during_right_clic(0, &hdata);
	if (scene->status.mouse_left_press)
		move_scene_during_left_clic(0, &hdata);
}

void print_scene_obj_img(t_object *object, t_img *img, t_scene *scene)
{
	t_object_mesh	*obj;
	obj = object->object;

	obj->new_rotation.yaw = 1;
	obj->new_offset = (t_offset){scene->cam.coord_axes[0],
		scene->cam.coord_axes[1], scene->cam.coord_axes[2]};
	update_size_obj(obj, ALL);
	print_obj_to_image(obj, img, object->id);

	object = object->next;
}

void print_all_obj(t_object *object, t_img *img, t_scene *scene)
{
	while (object)
	{

		print_scene_obj_img(object, img, scene);
		scene->cam.coord_axes = (t_v4f){0,0,0,0};
			object = object->next;
	}
	update_gizmo_position(scene);
}

int	loop(void *data, t_img *img, t_screen *screen)
{
	t_scene			*scene;

	scene = data;
	loop_hooks(scene, img, screen);
	print_all_obj(scene->object, img, scene);
	update_scene(scene);
	rt_print_img_screen(img, screen, 0, 0);
	if (scene->status.object_selected_id)
	{
		rt_set_image_color(scene->asset.gizmo_img, 0);
		print_obj_to_image(scene->asset.gizmo_translate, scene->asset.gizmo_img, 1);
		rt_print_img_screen(scene->asset.gizmo_img, screen, 0, 0);
	}
	return (0);
}

int	is_valid_format(char *file)
{
	size_t	size_file;

	size_file = ft_strlen(file);
	return (!ft_strncmp((file + size_file - 4), ".obj", 4));
}

void	open_file_dialog(void *data)
{
	t_scene	*scene;
	char	filename[1024];
	FILE	*fp;

	scene = data;
	fp = popen("zenity --file-selection --title=\"Select a file\"", "r");
	if (fp == NULL)
	{
		rt_error_window("Failed to run zenity command\n");
		return ;
	}
	if (fgets(filename, sizeof(filename), fp) != NULL)
	{
		filename[strcspn(filename, "\n")] = 0;
		ft_printf("Selected file: %s\n", filename);
	}
	else
	{
		rt_error_window("No file selected.\n");
		return ;
	}
	pclose(fp);
	if (!is_valid_format(filename))
		rt_error_window("file Format not supported\n");
	else
	{
		t_object_mesh *obj = parse_obj(filename, NULL);
		add_object(scene, obj, OBJECT_OBJ);
		obj->new_offset.x = 0;
		obj->new_offset.y = 0;
		obj->new_offset.z = 0;
		update_size_obj(scene->object->object, ALL | CENTER);
		down_center(scene->object->object);
	}
}

void	non(void *non)
{
	(void)non;
	printf("click on button omg\n");
}

void add_tea_pot(void *data)
{
	t_scene *scene;

	scene = data;
	t_object_mesh *obj = parse_obj("model/resources/teapot2.obj", NULL);
	add_object(scene, obj, OBJECT_OBJ);
	update_size_obj(scene->object->object, ALL | CENTER);
	down_center(scene->object->object);
}

int	main(int ac, char **av)
{
	t_screen	*screen;
	t_scene	scene;

	screen = rt_init();
	if (!screen)
		return (1);
	if (scene_init(&scene))
	{
		rt_destroy(screen);
		return (1);
	}

	// test function need to be replace with a function that load obj or rt scene
	if (av[1])
	{
		if (!is_valid_format(av[1]))
			rt_error_window("file Format not supported\n");
		else
		{
			add_object(&scene, parse_obj(av[1], NULL), OBJECT_OBJ);
			update_size_obj(scene.object->object, ALL | CENTER);
			down_center(scene.object->object);
		}
	}


	// test button need to be rm
	rt_add_text_button_top(screen, "file", &scene, open_file_dialog);
	rt_add_text_button_top(screen, "yoo", &scene, add_tea_pot);
	rt_add_text_button_top(screen, "comment", NULL, non);
	rt_add_text_button_top(screen, "ca", NULL, non);
	rt_add_text_button_top(screen, "va", NULL, non);



	rt_loop(&scene, screen, loop);
	rt_destroy(screen);
	return (ac);
}
