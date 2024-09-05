/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 19:59:22 by babonnet          #+#    #+#             */
/*   Updated: 2024/07/18 13:48:58 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_sign(int c)
{
	int	sign;

	sign = 1;
	if (c == '+' || c == '-')
	{
		if (c == '-')
			sign = -sign;
	}
	return (sign);
}

float	ft_atof(const char *str)
{
	float	nb;
	float	sign;
	float	decimal;

	nb = 0.0f;
	while (ft_isspace(*str))
		str++;
	sign = ft_sign(*str);
	if (*str == '+' || *str == '-')
		str++;
	while (ft_isdigit(*str))
	{
		nb = (nb * 10.0f) + (*str - 48);
		str++;
	}
	if (*str != '.')
		return (nb * sign);
	decimal = 0.1f;
	while (ft_isdigit(*++str))
	{
		nb += (float)(*str - 48) * decimal;
		decimal *= 0.1f;
	}
	return (nb * sign);
}
