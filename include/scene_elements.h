/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_elements.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 22:17:28 by babonnet          #+#    #+#             */
/*   Updated: 2024/03/12 00:04:07 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_ELEMENTS_H
# define SCENE_ELEMENTS_H

# include <stddef.h>

typedef float		__attribute__((aligned(16), vector_size(16))) t_v4f;
typedef void		t_texture_file;

enum				e_file_type
{
	FILE_TYPE_OBJ = 0,
	FILE_TYPE_MATH
};

typedef struct s_rotation
{
	double			pitch;
	double			yaw;
	double			roll;
}					t_rotation;

typedef struct s_offset
{
	double			x;
	double			y;
	double			z;
}					t_offset;

// might add vertex_texture
typedef struct s_face
{
	size_t			vertex_1;
	size_t			vertex_2;
	size_t			vertex_3;

	size_t			vertex_normal_1;
	size_t			vertex_normal_2;
	size_t			vertex_normal_3;
}					t_face;

// better texture management uv bump map etc
typedef struct s_mesh
{
	t_v4f			*vertex;
	t_v4f			*normal;
	t_face			*face;
}					t_mesh;

typedef struct s_object
{
	char			*file_name;
	e_file_type		file_type;
	t_mesh			*mesh;
	t_texture_file	*texture;
	t_rotation		rotation;
	t_offset		offset;
	double			scale;
	struct s_object	*next;
}					t_object;

typedef struct s_camera
{
	t_v4f			coord;
	t_rotation		rotation;
	struct s_camera	*next;
}					t_camera;

typedef struct s_scene
{
	t_camera		*cam;
	t_object		*object;
}					t_scene;

#endif
