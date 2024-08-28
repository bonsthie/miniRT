/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bonsthie <bonsthie@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 13:27:24 by bonsthie          #+#    #+#             */
/*   Updated: 2024/08/23 17:22:18 by bonsthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../hook/_hook.h"
#include "miniRT.h"
#include "object.h"
#include <rt_driver.h>
#include <rt_mesh_obj.h>
#include <rt_scene_elements.h>

bool	init_hooks(t_scene *scene, t_img *img, t_screen *screen)
{
	static struct s_hook_data	data;

	data.scene = scene;
	data.screen = screen;
	data.img = img;
	hook_creation(screen, &data);
	return (false);
}

void	loop_hooks(t_scene *scene, t_img *img, t_screen *screen)
{
	static bool					init_hooks_bool = true;
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

void	print_scene_obj_img(t_object *object, t_img *img, t_scene *scene)
{
	t_object_mesh	*obj;

	obj = object->object;
	obj->new_offset = (t_offset){scene->cam.coord_axes[0],
		scene->cam.coord_axes[1], scene->cam.coord_axes[2]};
	update_size_obj(obj, ALL);
	print_obj_to_image(obj, img, object->id);
	object = object->next;
}

void	print_all_obj(t_object *object, t_img *img, t_scene *scene)
{
	while (object)
	{
		print_scene_obj_img(object, img, scene);
		scene->cam.coord_axes = (t_v4f){0, 0, 0, 0};
		object = object->next;
	}
	update_gizmo_position(scene);
}

int	editor(t_scene *scene, t_img *img, t_screen *screen)
{
	scene->prev_mouse_3d = scene->mouse_3d;
	scene->mouse_3d = get_mouse_pos_3d(screen);
	loop_hooks(scene, img, screen);
	update_scene(scene);
	print_all_obj(scene->object, img, scene);
	rt_print_img_screen(img, screen, 0, 0);
	if (scene->status.object_selected_id && scene->status.gizmo_selected)
	{
		if (scene->status.gizmo_axe_selected)
			gizmo_move_object(scene);
		rt_set_image_color(scene->asset.gizmo_img, 0);
		if (scene->status.gizmo_selected == GIZMO_TRANSLATE)
			print_obj_to_image(scene->asset.gizmo_translate, scene->asset.gizmo_img, 1);
		else if (scene->status.gizmo_selected == GIZMO_SCALE)
			print_obj_to_image(scene->asset.gizmo_scale, scene->asset.gizmo_img, 1);
		else if (scene->status.gizmo_selected == GIZMO_ROTATE)
			print_obj_to_image(scene->asset.gizmo_rotate, scene->asset.gizmo_img, 1);
		rt_print_img_screen(scene->asset.gizmo_img, screen, 0, 0);
	}
	return (0);
}
