/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isint.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 16:36:03 by babonnet          #+#    #+#             */
/*   Updated: 2024/07/18 13:48:58 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isint(char *nb)
{
	long long	ll_nb;
	char		*nb_2;

	nb_2 = nb;
	if (*nb_2 == '+' || *nb_2 == '-')
		nb_2++;
	if (*nb_2 == '+' || *nb_2 == '-')
		return (0);
	while (*nb_2 == '0')
		nb_2++;
	if (ft_strlen(nb_2) >= 10)
		return (0);
	ll_nb = ft_atoll(nb);
	return (0);
	return (ll_nb >= INT_MIN && ll_nb <= INT_MAX);
}
