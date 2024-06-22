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

#include "driver/rasterizer/_rt_rasterizer.h"
#include "hook/_hook.h"
#include "miniRT.h"
#include "object.h"
#include <rt_driver.h>
#include <rt_mesh_obj.h>
#include <rt_scene_elements.h>
#include <stdio.h>
#include <string.h>

t_screen	*screen;

bool	init_hooks(t_scene *scene, t_img *img, t_screen *screen)
{
	static struct s_hook_data	data;

	data.scene = scene;
	data.screen = screen;
	data.img = img;
	hook_creation(screen, &data);
	return (false);
}

int	loop(void *data, t_img *img, t_screen *screen)
{
	t_scene *scene = data;
	t_object_mesh	*obj;
	t_object		*tmp;
	static bool		init_hooks_bool = true;

	static struct s_hook_data	hdata;

	hdata.scene = scene;
	hdata.screen = screen;
	hdata.img = img;

	if (init_hooks_bool == true)
		init_hooks_bool = init_hooks(scene, img, screen);
	during_right_clic(0, &hdata);
	during_left_clic(0, &hdata);
	tmp = scene->object;
	while (tmp)
	{
		obj = tmp->object;
		print_obj_to_image(obj, img, tmp->id);

		obj->new_rotation.yaw = 1;

		obj->new_offset = (t_offset){scene->cam->coord_axes[0],
			scene->cam->coord_axes[1], scene->cam->coord_axes[2]};
		update_size_obj(obj, ALL);
		scene->cam->coord_axes = (t_v4f){0,0,0,0};

		tmp = tmp->next;
	}
	update_scene(scene->object, scene->cam);
	rt_print_img_screen(img, screen, 0, 0);
	return (0);
}

int	is_valid_format(char *file)
{
	size_t	size_file;

	size_file = ft_strlen(file);
	return (!ft_strncmp((file + size_file - 4), ".obj", 4));
}

void	save_vec(t_object_mesh *object)
{
	for (size_t i = 0; i < object->mesh.size_mesh.vertex; i++)
		object->mesh.vertex_init[i] = object->mesh.vertex[i].v4f;
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
		save_vec(scene->object->object);
		update_size_obj(scene->object->object, ALL | CENTER);
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
	t_camera	cam;

	scene.object = NULL;

	scene.cam = &cam;
	cam.coord_axes = (t_v4f){0, 0, 0, 0};
	cam.coord_translation = (t_v4f){0, 0, 0, 0};
	cam.rotation = (t_rotation){0, 0, 0};
	cam.zoom = 100;
	cam.move_usage = NO_MOVE;

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
			save_vec(scene.object->object);
			update_size_obj(scene.object->object, ALL | CENTER);
		}
	}
	rt_add_text_button_top(screen, "file", &scene, open_file_dialog);
	rt_add_text_button_top(screen, "yoo", NULL, non);
	rt_add_text_button_top(screen, "comment", NULL, non);
	rt_add_text_button_top(screen, "ca", NULL, non);
	rt_add_text_button_top(screen, "va", NULL, non);
	rt_loop(&scene, screen, loop);
	rt_destroy(screen);
	return (ac);
}
