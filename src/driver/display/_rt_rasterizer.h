/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _rt_rasterizer.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 19:33:52 by babonnet          #+#    #+#             */
/*   Updated: 2024/08/19 16:36:31 by bonsthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _RT_RASTERIZER_H
# define _RT_RASTERIZER_H

# include <immintrin.h>
# include <miniRT.h>
# include <rt_driver.h>

# define FIXED_ORDER 8

typedef struct s_line_param
{
	int			first_point;
	int			second_point;
	int			d;
	int			s;
}				t_line_param;

typedef struct s_vertex
{
	t_vec3		position;
	t_vec3		normal;

}				t_vertex;

typedef struct s_tri
{
	t_vertex	vertex1;
	t_vertex	vertex2;
	t_vertex	vertex3;
	int			id;
}				t_tri;

typedef struct s_bbox
{
	int			min_x;
	int			min_y;
	int			max_x;
	int			max_y;
}				t_bbox;

typedef union u_edge_coef
{
	__m256i		avx_edge;
	struct
	{
		int		dwdx2;
		int		dwdy2;
		int		dwdx0;
		int		dwdy0;
		int		dwdx1;
		int		dwdy1;
	};
}				t_edge_coef;

void			plot_line(t_vec3 v1, t_vec3 v2, t_img *img, unsigned int color);
void			rast_tri(t_tri triangle, t_img *img, unsigned int color);

#endif
