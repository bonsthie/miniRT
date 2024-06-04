/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_mesh_obj.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 23:14:48 by babonnet          #+#    #+#             */
/*   Updated: 2024/06/05 00:06:41 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_MESH_OBJ_H
# define RT_MESH_OBJ_H

# include "libft.h"
# include <stddef.h>
# include <rt_driver.h>

typedef struct s_texture
{
	int				width;
	int				height;
	void			*file;
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

// A triangular face generally defined by three points but can could be more
typedef struct s_face
{
	t_point			*point;
	size_t			count;
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
	union vec			*vertex;
	union vec			*normal;
	t_texture_coord	*texture_coord;
	t_face			*face;
	t_size_mesh		size_mesh;
}					t_mesh;

typedef struct s_object_mesh
{
	char			*file_name;
	t_list			*file;
	int				fd;
	t_mesh			mesh;
	t_texture		texture;
	t_rotation		rotation;
	t_rotation		new_rotation;
	t_offset		offset;
	t_offset		new_offset;
	float			scale;
	float			new_scale;
	union vec		center;
}					t_object_mesh;

void update_size_obj(t_object_mesh *object);

#endif
