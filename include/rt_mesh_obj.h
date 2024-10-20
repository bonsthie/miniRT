/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_mesh_obj.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 23:14:48 by babonnet          #+#    #+#             */
/*   Updated: 2024/09/17 14:43:33 by bonsthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_MESH_OBJ_H
# define RT_MESH_OBJ_H

# include <libft.h>
# include <miniRT.h>
# include <rt_driver.h>
# include <stddef.h>

typedef struct s_texture
{
	int							width;
	int							height;
	void						*file;
}								t_texture;

// 3D rotation, specified in Euler angles.
typedef struct s_rotation
{
	float						pitch;
	float						yaw;
	float						roll;
}								t_rotation;

// 3D position or offset.
typedef struct s_offset
{
	float						x;
	float						y;
	float						z;
}								t_offset;

// References to a vertex, its normal, and texture coordinate in a mesh.
typedef struct s_point
{
	size_t						vertex;
	size_t						normal;
	size_t						texture;
}								t_point;

// A triangular face generally defined by three points but can could be more
typedef struct s_face
{
	t_point						*point;
	uint8_t						count;
	union u_color				color;
}								t_face;

typedef struct s_texture_coord
{
	float						u;
	float						v;
}								t_texture_coord;

typedef struct s_size_mesh
{
	size_t						vertex;
	size_t						normal;
	size_t						texture;
	size_t						face;
}								t_size_mesh;

typedef struct s_mesh
{
	t_v4f						*vertex_init;
	union u_vec					*vertex;
	union u_vec					*normal;
	t_texture_coord				*texture_coord;
	t_face						*face;
	t_size_mesh					size_mesh;
}								t_mesh;

struct							s_object_metadata
{
	char						*file_name;
	t_list						*file;
	int							fd;
};

typedef struct s_object_mesh
{
	struct s_object_metadata	metadata;

	t_mesh						mesh;
	t_texture					texture;

	t_rotation					rotation;
	t_rotation					new_rotation;

	t_offset					offset;
	t_offset					new_offset;

	float						scale;
	float						new_scale;

	union u_vec					center;
	union u_vec					relative_center;
	union u_vec					saving_point;
	union u_vec					relative_point;

}								t_object_mesh;

enum							e_setting_update_size_obj
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

void							update_size_obj(t_object_mesh *object,
									uint8_t setting);

void	find_center(t_object_mesh *object, t_v4f *vertex, t_v4f *center);
void	down_center(t_object_mesh *object);

#endif
