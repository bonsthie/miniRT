/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 11:40:46 by bbonnet           #+#    #+#             */
/*   Updated: 2024/07/18 13:48:58 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memmove(void *destination, const void *source, size_t num)
{
	unsigned char	*src;
	unsigned char	*dest;

	src = (unsigned char *) source;
	dest = (unsigned char *) destination;
	if (src == dest)
		return (destination);
	if (src > dest)
	{
		while (num--)
			*dest++ = *src++;
	}
	else
	{
		src += num;
		dest += num;
		while (num--)
			*(--dest) = *(--src);
	}
	return (destination);
}
