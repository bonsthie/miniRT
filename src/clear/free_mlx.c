/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 15:17:09 by babonnet          #+#    #+#             */
/*   Updated: 2024/03/22 18:16:11 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "mlx.h"
#include "mlx_data.h"

void __attribute__((destructor))free_mlx_data(void)
{
	t_mlx *mlx;

	mlx = get_mlx();
	return ;
	if (mlx->connection)
	{
		mlx_loop_end(mlx->connection);
		if (mlx->image)
			mlx_destroy_image(mlx->connection, mlx->image);
		if (mlx->window)
			mlx_destroy_window(mlx->connection, mlx->window);
		mlx_destroy_display(mlx->connection);
		ft_printf("%p   %p    %p\n", mlx->image, mlx->window, mlx->connection);
	}
}
