/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_scene_elements.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 22:17:28 by babonnet          #+#    #+#             */
/*   Updated: 2024/06/22 20:07:31 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_SCENE_ELEMENTS_H
# define RT_SCENE_ELEMENTS_H

# include "miniRT.h"
# include "rt_driver.h"
# include <rt_mesh_obj.h>
#include <stdint.h>

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
}			t_cam_movement;

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

/**
 * @Main structure of the project defining the components of a scene.
 * @object Pointer to the first object in the scene,
	forming a linked list of all objects.
 * @light Pointer to the first light source in the scene,
	forming a linked list of all lights.
 * @cam Pointer to the camera used to view the scene.
 */
typedef struct s_scene
{
	t_object		*object;
	t_light			*light;
	t_camera		cam;

	t_asset			asset;

}					t_scene;

void	update_scene(t_object *object, t_camera *cam);
int scene_init(t_scene *scene);

#endif
