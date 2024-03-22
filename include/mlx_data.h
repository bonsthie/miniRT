/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_data.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 13:18:38 by babonnet          #+#    #+#             */
/*   Updated: 2024/03/22 16:21:52 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLX_DATA_H
#define MLX_DATA_H

# ifndef WIDTH
#  define WIDTH 1920
# endif

# ifndef HEIGHT
#  define HEIGHT 1080
# endif

typedef struct s_mlx
{
	void				*connection;
	void				*window;
	void				*image;
	int					mouse_x;
	int					mouse_y;
}						t_mlx;

t_mlx *get_mlx(void);
t_mlx *init_mlx_data(void);


void free_mlx_data(void);

#endif
