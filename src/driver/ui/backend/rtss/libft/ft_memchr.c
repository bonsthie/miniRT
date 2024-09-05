/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 23:25:03 by bbonnet           #+#    #+#             */
/*   Updated: 2024/07/18 13:48:58 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memchr(const void *str, int c, size_t n)
{
	size_t					i;
	const unsigned char		*str_cp;

	i = 0;
	str_cp = (const unsigned char *) str;
	while (n - i > 0)
	{
		if (str_cp[i] == (const unsigned char) c)
			return ((void *) &str_cp[i]);
		i++;
	}
	return (NULL);
}
