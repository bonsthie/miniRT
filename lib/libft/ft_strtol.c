/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtol.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 11:24:46 by babonnet          #+#    #+#             */
/*   Updated: 2024/07/18 13:48:58 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static inline int	ft_index(char *str, char c)
{
	char	*tmp;

	tmp = str;
	c = ft_toupper(c);
	while (*tmp && (ft_toupper(*tmp) != c))
		tmp++;
	if (!tmp)
		return (0);
	return (tmp - str);
}

static long int	_strtol(char *nptr, char *base, int base_size)
{
	long int	nb;
	int			i;
	int			sign;

	nb = 0;
	sign = 1;
	while (ft_isspace(*nptr))
		nptr++;
	if (*nptr == '-' || *nptr == '+')
		sign = (int)2 * (0.5 - (*(nptr++) == '-'));
	while (*nptr)
	{
		i = ft_index(base, *(nptr++));
		if (i < 0)
			return (0);
		nb = nb * base_size + i;
	}
	return (sign * nb);
}

long int	ft_strtol(char *nptr, char *base, int base_size)
{
	char	*base_s;

	base_s = (char *)"0123456789ABCDEF";
	if (!nptr)
		return (0);
	if (!ft_strncmp(nptr, "0x", 2))
		return (ft_strtol(nptr + 2, base_s, 16));
	if (!ft_strncmp(nptr, "0b", 2))
		return (ft_strtol(nptr + 2, base_s, 2));
	if (!base || base_size == 0)
		return (ft_strtol(nptr, base_s, 10));
	return (_strtol(nptr, base, base_size));
}
