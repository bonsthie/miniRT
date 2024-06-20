/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 18:58:46 by babonnet          #+#    #+#             */
/*   Updated: 2024/06/19 16:04:49 by yroussea         ###   ########.fr       */
/* ************************************************************************** */

#include "object.h"
#include <rt_driver.h>
#include <rt_mesh_obj.h>
#include <rt_scene_elements.h>
#include <stdio.h>
#include <string.h>

t_screen	*screen;

int	loop(t_scene *scene, t_img *img, t_screen *screen)
{
	t_object_mesh	*obj;

	if (scene->object)
	{
		obj = scene->object->object;
		print_obj_to_image(obj, img, scene->object->id);
		obj->new_rotation.yaw = 1;
		update_size_obj(obj, ALL | ROT_CENTER_OBJ);
	}
	rt_print_img_screen(img, screen, 0, 0);
	return (0);
}

int is_valid_format(char *file)
{
	size_t size_file;

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
		rt_error_window(screen, "Failed to run zenity command\n");
		return ;
	}
	if (fgets(filename, sizeof(filename), fp) != NULL)
	{
		filename[strcspn(filename, "\n")] = 0;
		ft_printf("Selected file: %s\n", filename);
	}
	else
	{
		rt_error_window(screen, "No file selected.\n");
		return ;
	}
	pclose(fp);
	if (!is_valid_format(filename))
		rt_error_window(screen, "file Format not supported\n");
	else
	{
		add_object(scene, parse_obj(filename, NULL), OBJECT_OBJ);
		update_size_obj(scene->object->object, ALL);
	}
}

void	non(void *non)
{
	(void)non;
	printf("click on button omg\n");
}

int	main(int ac, char **av)
{
	t_scene		scene;

	scene.object = NULL;
	scene.object = NULL;
	screen = rt_init();
	if (!screen)
		return (1);
	if (av[1])
	{
		if (!is_valid_format(av[1]))
			rt_error_window(screen, "file Format not supported\n");
		else
		{
			add_object(&scene, parse_obj(av[1], NULL), OBJECT_OBJ);
			update_size_obj(scene.object->object, ALL | ROT_CENTER_OBJ);
		}
	}
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
