/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_scene_elements.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 22:17:28 by babonnet          #+#    #+#             */
/*   Updated: 2024/08/20 14:50:09 by bonsthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_SCENE_ELEMENTS_H
# define RT_SCENE_ELEMENTS_H

# include "miniRT.h"
# include "rt_driver.h"
# include <rt_mesh_obj.h>
# include <stdbool.h>

typedef struct s_object
{
	t_file_type		file_type;
	int				id;
	void			*object;
	struct s_object	*next;
}					t_object;

typedef enum s_cam_movement
{
	NO_MOVE = 1u,
	ZOOM = 1u << 1,
	ROTATE = 1u << 2,
	MOVING = 1u << 3,
}					t_cam_movement;

typedef struct s_camera
{
	t_cam_movement	move_usage;
	t_v4f			coord_axes;
	t_v4f			coord_translation;
	float			zoom;
	t_rotation		rotation;
	int				fov;
}					t_camera;

// may be add angle of the light
typedef struct s_light
{
	t_v4f			coord;
	t_rotation		rotation;
	int				color;
	int				intensity;
	struct s_light	*next;
}					t_light;

typedef struct s_asset
{
	t_object_mesh	*gizmo_translate;
	t_object_mesh	*gizmo_rotate;
	t_object_mesh	*gizmo_scale;
	t_img			*gizmo_img;
}					t_asset;

enum				e_gizmo_selected
{
	GIZMO_NO,
	GIZMO_TRANSLATE,
	GIZMO_ROTATE,
	GIZMO_SCALE,
};

enum				e_gimzo_axe_selected
{
	GIZMO_AXE_NONE,
	GIZMO_AXE_X,
	GIZMO_AXE_Y,
	GIZMO_AXE_Z
};

enum				e_viewport_selected
{
	VP_EDITOR,
	VP_RAYTRACER
};

typedef struct s_status
{
	short			object_selected_id;
	uint8_t mouse_left_press : 1;
	uint8_t mouse_right_press : 1;
	uint8_t gizmo_selected : 3;
	uint8_t gizmo_axe_selected : 2;
	uint8_t viewport_status : 1;
}					t_status;

typedef int (*t_loop_func)(t_scene *, t_img *, t_screen *);

typedef struct s_hook {
	void *keyup;
	void *keydown;

	void *mouseup;
	void *mousedown;

	void *mousewheel;
} t_hook;

typedef struct s_loop {
	t_loop_func f;
	t_hook		hook;
} t_loop;

typedef struct s_scene
{
	t_object		*object;
	t_light			*light;
	t_camera		cam;

	t_loop			loop;

	t_asset			asset;
	t_status		status;

	union u_vec		mouse_3d;
	union u_vec		prev_mouse_3d;
}					t_scene;

int					scene_init(t_scene *scene);

void				update_scene(t_scene *scene);
void				rotate_center(t_v4f *tr, t_v4f vertex, t_v4f *result);
void				update_mouse_3d_pos(union u_vec *mouse_3d, t_v4f tr[4]);
union u_vec			get_mouse_pos_3d(t_screen *screen);
union u_vec			mouse_pose_relative_to_object(union u_vec mouse_3d,
						t_object *object);

void				gizmo_move_object(t_scene *scene);

void				select_viewport_raytracer(void *data);
void				select_viewport_editor(void *data);

#endif
