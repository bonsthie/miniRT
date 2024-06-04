/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_scene_elements.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 22:17:28 by babonnet          #+#    #+#             */
/*   Updated: 2024/06/04 17:06:38 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_ELEMENTS_H
# define SCENE_ELEMENTS_H

#include "miniRT.h"
# include <rt_mesh_obj.h>
# include <stddef.h>

typedef struct s_object
{
	t_file_type		file_type;
	void			*object;
	struct s_object	*next;
}					t_object;

typedef struct s_camera
{
	t_v4f			coord;
	t_rotation		rotation;
	int				fov;
	struct s_camera	*next;
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
	t_camera		*cam;

}					t_scene;

#endif
