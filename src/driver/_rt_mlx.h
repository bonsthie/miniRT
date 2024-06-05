/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _rt_mlx.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 17:59:40 by babonnet          #+#    #+#             */
/*   Updated: 2024/06/05 12:27:40 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _RT_MLX_H
# define _RT_MLX_H

# ifndef RT_WIN_NAME
#  define RT_WIN_NAME "RT"
# endif

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
	int				zbuffer[RT_HEIGHT][RT_WIDTH];    /**< Z-buffer array for depth information */
	unsigned int	color[RT_HEIGHT][RT_WIDTH];      /**< Color buffer array */
	int				obj_id[RT_HEIGHT][RT_WIDTH];     /**< Object ID buffer array */
} t_img;

typedef struct s_rt
{
	void *mlx;
	void *win;
} t_rt;

typedef struct s_mlx
{
	void *connection;
	void *window;
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
