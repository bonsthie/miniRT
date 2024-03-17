/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh_obj.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 23:14:48 by babonnet          #+#    #+#             */
/*   Updated: 2024/03/17 00:55:55 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MESH_OBJ_H
# define MESH_OBJ_H

# include "miniRT.h"
# include <stddef.h>

typedef struct s_texture
{
	int				width;
	int				height;
	t_image			*file;
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
	t_point			point1;
	t_point			point2;
	t_point			point3;
}					t_face;

typedef struct s_texture_coord
{
	float			u;
	float			v;
}					t_texture_coord;

typedef struct s_size_mesh
{
	size_t			vertex;
	size_t			normal;
	size_t			texture;
	size_t			face;
}					t_size_mesh;

typedef struct s_mesh
{
	t_v4f			*vertex;
	t_v4f			*normal;
	t_texture_coord	*texture_coord;
	t_face			*face;
	t_size_mesh		size_mesh;
}					t_mesh;

typedef struct s_object_mesh
{
	char			*file_name;
	t_mesh			mesh;
	t_texture		texture;
	t_rotation		rotation;
	t_offset		offset;
	float			scale;
}					t_object_mesh;

#endif
