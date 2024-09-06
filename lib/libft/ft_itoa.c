/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 14:51:12 by babonnet          #+#    #+#             */
/*   Updated: 2024/07/18 13:48:58 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static int	calcul_length(int nb)
{
	int	count;

	count = 0;
	if (nb == 0)
		return (1);
	if (nb < 0)
		count++;
	while (nb)
	{
		count++;
		nb /= 10;
	}
	return (count);
}

char	*ft_itoa(int nb)
{
	char	*dest;
	int		dest_len;
	long	n;

	n = nb;
	dest_len = calcul_length(n);
	dest = malloc((dest_len + 1) * sizeof(char));
	if (!dest)
		return (NULL);
	dest[dest_len--] = 0;
	if (n == 0)
		dest[0] = '0';
	if (n < 0)
	{
		dest[0] = '-';
		n = -n;
	}
	while (n)
	{
		dest[dest_len--] = n % 10 + '0';
		n /= 10;
	}
	return (dest);
}
