/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_mesh_obj.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 23:14:48 by babonnet          #+#    #+#             */
/*   Updated: 2024/06/20 12:59:03 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_MESH_OBJ_H
# define RT_MESH_OBJ_H

# include <rt_driver.h>
# include <libft.h>
# include <miniRT.h>
# include <stddef.h>

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
	union u_vec		*vertex;
	union u_vec		*normal;
	t_texture_coord	*texture_coord;
	t_face			*face;
	t_size_mesh		size_mesh;
}					t_mesh;

struct s_object_metadata
{
	char			*file_name;
	t_list			*file;
	int				fd;
};

typedef struct s_object_mesh
{
	struct s_object_metadata metadata;

	t_mesh			mesh;
	t_texture		texture;
	union u_color	color;

	t_rotation		rotation;
	t_rotation		new_rotation;

	t_offset		offset;
	t_offset		new_offset;

	float			scale;
	float			new_scale;

	union u_vec		center;
}					t_object_mesh;

enum				e_setting_update_size_obj
{
	ROT_YAW = 1u,
	ROT_PITCH = 1u << 1,
	ROT_ROLL = 1u << 2,
	ALL_ROTATION = (1u << 3) - 1,
	ROT_CENTER_OBJ = 1u << 3,
	TRANSLATE = 1u << 4,
	SCALE = 1u << 5,
	ALL = (1u << 6) - 1 - ROT_CENTER_OBJ,
	CENTER = 1u << 6
};

void				update_size_obj(t_object_mesh *object, uint8_t setting);

#endif
