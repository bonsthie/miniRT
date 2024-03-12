/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_elements.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 22:17:28 by babonnet          #+#    #+#             */
/*   Updated: 2024/03/12 02:29:39 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_ELEMENTS_H
# define SCENE_ELEMENTS_H

# include <stddef.h>

// Aligned vector types for optimal hardware utilization.
typedef float		__attribute__((aligned(16), vector_size(16))) t_v4f;
// Generic pointer for texture data, to be defined based on specific library usage.
typedef void		t_texture_file;

// Enum to distinguish between different file types supported by the engine.
enum				e_file_type
{
	FILE_TYPE_OBJ = 0,
	FILE_TYPE_MATH
};

typedef struct s_texture
{
	int				width;
	int				height;
	t_texture_file	*file;
}					t_texture;

// 3D rotation, specified in Euler angles.
typedef struct s_rotation
{
	float			pitch;
	float			yaw;
	float			roll;
}					t_rotation;

// 3D position or offset.
typedef struct s_offset
{
	float			x;
	float			y;
	float			z;
}					t_offset;

// References to a vertex, its normal, and texture coordinate in a mesh.
typedef struct s_point
{
	size_t			vertex;
	size_t			normal;
	size_t			texture;
}					t_point;


// A triangular face defined by three points.
typedef struct s_face
{
	s_point			point1;
	s_point			point2;
	s_point			point3;
}					t_face;

typedef struct s_texture_coord
{
	float			u;
	float			v;
}					t_texture_coord;

typedef struct s_mesh
{
	t_v4f			*vertex;
	t_v4f			*normal;
	t_texture_coord	*texture_coord;
	t_face			*face;
}					t_mesh;

typedef struct s_object
{
	char			*file_name;
	e_file_type		file_type;
	t_mesh			*mesh;
	t_texture		*texture;
	t_rotation		rotation;
	t_offset		offset;
	float			scale;
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
	struct s_camera	*next;
}					t_light;

/**
 * @Main structure of the project defining the components of a scene.
 * @object Pointer to the first object in the scene, forming a linked list of all objects.
 * @light Pointer to the first light source in the scene, forming a linked list of all lights.
 * @cam Pointer to the camera used to view the scene.
 */
typedef struct s_scene
{
	t_object		*object;
	t_light			*light;
	t_camera		*cam;
}					t_scene;

#endif

