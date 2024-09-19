/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bonsthie <bonsthie@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 19:14:27 by babonnet          #+#    #+#             */
/*   Updated: 2024/09/19 15:40:51 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "object.h"
#include <rt_driver.h>
#include <rt_driver_button.h>
#include <rt_mesh_obj.h>
#include <rt_scene_elements.h>
#include <stdio.h>
#include <string.h>

int	loop(void *data, t_img *img, t_screen *screen)
{
	t_scene	*scene;

	scene = data;
	return (scene->loop.f(scene, img, screen));
}

int	is_valid_format(char *file)
{
	size_t	size_file;

	size_file = ft_strlen(file);
	return (!ft_strncmp((file + size_file - 4), ".obj", 4));
}

void	open_file_dialog(void *data)
{
	t_scene			*scene;
	char			filename[1024];
	FILE			*fp;
	t_object_mesh	*obj;

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
		obj = parse_obj(filename, NULL);
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

void	add_tea_pot(void *data)
{
	t_scene			*scene;
	t_object_mesh	*obj;

	scene = data;
	obj = parse_obj("model/resources/teapot2.obj", NULL);
	add_object(scene, obj, OBJECT_OBJ);
	update_size_obj(scene->object->object, ALL | CENTER);
	down_center(scene->object->object);
}

int	main(int ac, char **av __attribute__((unused)))
{
	if (ac < 2)
		return (1);
	t_htab *tab = rt_create_stylesheet("asset/button.rtss");
	t_screen			*screen;
	t_scene				scene;
	t_button_setting	button;

	screen = rt_init();
	if (!screen)
		return (1);
	if (scene_init(&scene))
	{
		rt_destroy(screen);
		return (1);
	}
	scene.status.object_selected_id = 0;
	// test function need to be replace with a function that load obj or rt scene
	/* if (av[1]) */
	/* { */
	/* 	if (!is_valid_format(av[1])) */
	/* 		rt_error_window("file Format not supported\n"); */
	/* 	else */
	/* 	{ */
	/* 		add_object(&scene, parse_obj(av[1], NULL), OBJECT_OBJ); */
	/* 		update_size_obj(scene.object->object, ALL | CENTER); */
	/* 		down_center(scene.object->object); */
	/* 	} */
	/* } */
	// test button need to be rm
	button.htab = tab;
	button.class = "button_solo";
	button.on_start = false;
	button.f = open_file_dialog;
	button.id = RT_SIMPLE_BUTTON;
	button.text = "file";
	button.style = TEXT;
	button.data = &scene;
	rt_add_text_button_top(screen, button);
	button.id = RT_SIMPLE_BUTTON;
	button.f = add_tea_pot;
	button.text = "yoo";
	rt_add_text_button_top(screen, button);
	// change the on_start to have as default
	button.class = "button_editor";
	button.id = 3;
	button.f = select_viewport_editor;
	button.data = &scene;
	button.text = "editor";
	button.on_start = true;
	rt_add_text_button_top(screen, button);
	button.class = "button_raytracer";
	button.id = 3;
	button.f = select_viewport_raytracer;
	button.text = "raytracer";
	button.on_start = false;
	rt_add_text_button_top(screen, button);
	rt_loop(&scene, screen, loop);
	rt_destroy(screen);
	free_scene_asset(&scene.asset);
	rt_destroy_stylesheet(tab);
	return (ac);
}
