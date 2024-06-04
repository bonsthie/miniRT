/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _rt_mlx.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 17:59:40 by babonnet          #+#    #+#             */
/*   Updated: 2024/06/04 19:26:52 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _RT_MLX_H
#define _RT_MLX_H

#include <rt_driver.h>
#include <rt_scene_elements.h>

typedef int (*scene_func)(t_scene *scene, t_img *img);

typedef struct s_mlx
{
	void				*connection;
	void				*window;
	void				*image;
	int					mouse_x;
	int					mouse_y;

	t_scene				*scene;
	t_img				*img;
	scene_func			scene_function;
}						t_mlx;

int init_mlx_data(t_mlx *mlx);
void free_mlx_data(void);
void	hook(t_mlx *mlx);

#endif
