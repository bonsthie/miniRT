/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normalize.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 14:49:42 by babonnet          #+#    #+#             */
/*   Updated: 2024/08/19 16:24:35 by bonsthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_driver.h"
#include "rt_math.h"

t_v4f	normalize(t_v4f n)
{
	float	mag;
	t_v4f	vmag;

	mag = magnitude(n);
	vmag = (t_v4f){mag, mag, mag, 1};
	return (n / vmag);
}
