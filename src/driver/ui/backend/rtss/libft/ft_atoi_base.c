/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 11:37:23 by babonnet          #+#    #+#             */
/*   Updated: 2024/07/18 13:48:58 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static inline int	ft_index(char *str, char c)
{
	char	*tmp;

	tmp = str;
	c = ft_toupper(c);
	while (*tmp && (*tmp != c))
		tmp++;
	if (!tmp)
		return (0);
	return (tmp - str);
}

int	ft_atoi_base(char *nptr, int base)
{
	static char	base_s[17] = "0123456789ABCDEF";
	long		n;
	int			i;
	int			sign;

	n = 0;
	sign = 1;
	while (ft_isspace(*nptr))
		nptr++;
	if (*nptr == '-' || *nptr == '+')
		sign = (int)2 * (0.5 - (*(nptr++) == '-'));
	while (*nptr)
	{
		i = ft_index(base_s, *(nptr++));
		if (i < 0)
			return (0);
		n = n * base + i;
	}
	return (sign * n);
}
