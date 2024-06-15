/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _rt_mlx.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 17:59:40 by babonnet          #+#    #+#             */
/*   Updated: 2024/06/10 13:48:06 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _RT_MLX_H
# define _RT_MLX_H

# include <rt_driver.h>
# include <rt_scene_elements.h>
# include "_rt_button.h"

typedef int				(*t_scene_func)(t_scene *scene, t_img *img,
					t_screen *screen);

typedef struct s_screen
{
	void				*mlx;
	void				*win;

	int					mouse_x;
	int					mouse_y;

	t_button			*button_top;
	t_button			*button_side;

	int					error_pid;
}						t_screen;

typedef struct s_img
{
	int					zbuffer[RT_HEIGHT][RT_WIDTH];
	unsigned int		color[RT_HEIGHT][RT_WIDTH];
	int					obj_id[RT_HEIGHT][RT_WIDTH];
}						t_img;

typedef struct s_mlx
{
	void				*connection;
	void				*window;

	t_scene_func		scene_function;

	t_scene				*scene;
	t_img				*img;
	t_screen			*screen;
}						t_mlx;

int						init_mlx_data(t_mlx *mlx);
void					free_mlx_data(void);
void					hook(t_mlx *mlx);
int						rt_error_signal(void);

#endif
