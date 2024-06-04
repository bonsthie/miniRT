/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _rt_mlx.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 17:59:40 by babonnet          #+#    #+#             */
/*   Updated: 2024/06/05 01:06:05 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _RT_MLX_H
#define _RT_MLX_H

#include <rt_driver.h>
#include <rt_scene_elements.h>

typedef struct s_screen
{
	void				*connection;
	void				*window;
} t_screen;

typedef int (*scene_func)(t_scene *scene, t_img *img, t_screen *screen);

typedef struct s_img
{
	int				zbuffer[HEIGHT][WIDTH];    /**< Z-buffer array for depth information */
	unsigned int	color[HEIGHT][WIDTH];      /**< Color buffer array */
	int				obj_id[HEIGHT][WIDTH];     /**< Object ID buffer array */
} t_img;

typedef struct s_mlx
{
	int					mouse_x;
	int					mouse_y;

	scene_func			scene_function;

	t_scene				*scene;
	t_img				*img;
	t_screen			screen;
}						t_mlx;

int init_mlx_data(t_mlx *mlx);
void free_mlx_data(void);
void	hook(t_mlx *mlx);

#endif
