/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix4by1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 13:38:38 by babonnet          #+#    #+#             */
/*   Updated: 2024/03/22 22:30:08 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "miniRT.h"

__attribute__((always_inline)) void	matrix_multiplication1x4(t_v4f *matrix,
												t_v4f vector, t_v4f *result)
{
	int		i;
	t_v4f	product;
	double	dot_product;

	*result = (t_v4f){0, 0, 0, 0};
	i = 0;
	while (i < 4)
	{
		product = matrix[i] * vector;
		dot_product = product[0] + product[1] + product[2] + product[3];
		(*result)[i] = dot_product;
		i++;
	}
}
