/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix4by4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 20:31:44 by babonnet          #+#    #+#             */
/*   Updated: 2024/06/11 19:18:11 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt_driver.h>
#include <immintrin.h>

void	matrix_multiplication4x4(t_v4f result[4], t_v4f a[4], t_v4f b[4])
{
	int		i;
	int		j;
	t_v4f	temp;
	t_v4f	replicated;

	i = 0;
	while (i < 4)
	{
		temp = (t_v4f){0, 0, 0, 0};
		j = 0;
		while (j < 4)
		{
			replicated = (t_v4f){a[i][j], a[i][j], a[i][j], a[i][j]};
			temp += replicated * b[j];
			j++;
		}
		result[i] = temp;
		i++;
	}
}
