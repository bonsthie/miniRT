/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _rt_mlx.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 17:59:40 by babonnet          #+#    #+#             */
/*   Updated: 2024/06/05 16:48:28 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _RT_MLX_H
# define _RT_MLX_H

# include <rt_driver.h>
# include <rt_scene_elements.h>

typedef int				(*t_scene_func)(t_scene *scene, t_img *img,
					t_screen *screen);
typedef void (t_button_func)(void *data);

enum e_button_type
{
	IMG,
	TXT,
	SEPARATOR,
};

#define TXT_BUTTON_SIDE 40

typedef struct s_button
{
	enum e_button_type	type;
	char				*name;
	void				*data;
	t_button_func		*func;
	struct s_button		*next;
}						t_button;

typedef struct s_screen
{
	void				*mlx;
	void				*win;

	int					mouse_x;
	int					mouse_y;

	t_button			*button_top;
	t_button			*button_side;
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

#endif
