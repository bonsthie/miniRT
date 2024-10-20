/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _rt_mlx.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 17:59:40 by babonnet          #+#    #+#             */
/*   Updated: 2024/08/20 19:28:18 by bonsthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _RT_MLX_H
# define _RT_MLX_H

# include "_rt_button.h"
# include <rt_driver.h>
# include <rt_scene_elements.h>

typedef int			(*t_scene_func)(void *data, t_img *img, t_screen *screen);

typedef int			(*t_hooks_function)(int key, void *data);

struct				s_hooks
{
	void			**hook_function[HOOK_COUNT];
	void			*data[HOOK_COUNT];
};

typedef struct s_screen
{
	void			*mlx;
	void			*win;

	int				mouse_x;
	int				mouse_y;

	t_button		*button_top;
	t_button		*button_side;

	struct s_hooks	hooks;
}					t_screen;

typedef struct s_mlx
{
	void			*connection;
	void			*window;

	t_scene_func	scene_function;

	void			*data;
	t_img			*img;
	t_screen		*screen;
}					t_mlx;

int					init_mlx_data(t_mlx *mlx);
void				free_mlx_data(void);
void				hook(t_mlx *mlx);

int					rt_error_signal(void);
int					*rt_get_error_pid(void);

#endif
