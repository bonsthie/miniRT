/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 18:58:46 by babonnet          #+#    #+#             */
/*   Updated: 2024/06/07 21:19:45 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene/object.h"
#include <rt_driver.h>
#include <rt_mesh_obj.h>
#include <rt_scene_elements.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>

int	loop(t_scene *scene, t_img *img, t_screen *screen)
{
	t_object_mesh	*obj;

	if (scene->object)
	{
		obj = scene->object->object;
		print_obj_to_image(obj, img);
		obj->new_rotation.yaw = 1;
		update_size_obj(obj);
	}
	rt_print_img_screen(img, screen, 0, 0);
	return (0);
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
		ft_printf("Failed to run zenity command\n");
		return ;
	}
	if (fgets(filename, sizeof(filename), fp) != NULL)
	{
		filename[strcspn(filename, "\n")] = 0;
		ft_printf("Selected file: %s\n", filename);
	}
	else
	{
		ft_printf("No file selected.\n");
		return ;
	}
	pclose(fp);
	add_object(scene, parse_obj(filename, NULL), OBJECT_OBJ);
}

void	non(void *non)
{
	(void)non;
	printf("click on button omg\n");
}

int	main(int ac, char **av)
{
	t_scene		scene;
	t_screen	*screen;

	scene.object = NULL;
	scene.object = NULL;
	if (av[1])
		add_object(&scene, parse_obj(av[1], NULL), OBJECT_OBJ);
	screen = rt_init();
	if (!screen)
		return (1);
	rt_add_text_button_top(screen, "file", &scene, open_file_dialog);
	rt_add_text_button_top(screen, "yoo", NULL, non);
	rt_add_text_button_top(screen, "comment", NULL, non);
	rt_add_text_button_top(screen, "ca", NULL, non);
	rt_add_text_button_top(screen, "va", NULL, non);
	(void)av;
	(void)ac;
	rt_loop(&scene, screen, loop);
	rt_destroy(screen);
}
