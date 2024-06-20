/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _rasterizer.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 19:33:52 by babonnet          #+#    #+#             */
/*   Updated: 2024/06/20 14:37:45 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _RASTERIZER_H
# define _RASTERIZER_H

# include <miniRT.h>
# include <rt_driver.h>

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

void			plot_line(t_vec3 v1, t_vec3 v2, t_img *img, unsigned int color);
void			rast_tri(t_tri triangle, t_img *img, unsigned int color);

#endif
