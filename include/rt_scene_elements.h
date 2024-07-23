/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_scene_elements.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 22:17:28 by babonnet          #+#    #+#             */
/*   Updated: 2024/07/21 20:21:30 by babonnet         ###   ########.fr       */
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


enum e_gizmo_selected
{
	GIZMO_NO,
	GIZMO_TRANSLATE,
	GIZMO_ROTATE,
	GIZMO_SCALE,
};

typedef struct s_status
{
	short			object_selected_id;
	bool			mouse_left_press;
	bool			mouse_right_press;
	uint8_t			gizmo_selected:3;
	uint8_t			padding:2;
}					t_status;

typedef struct s_scene
{
	t_object		*object;
	t_light			*light;
	t_camera		cam;

	t_asset			asset;
	t_status		status;
}					t_scene;

void				update_scene(t_scene *scene);
int					scene_init(t_scene *scene);

#endif
