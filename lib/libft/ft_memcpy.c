/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 10:43:29 by bbonnet           #+#    #+#             */
/*   Updated: 2024/07/18 13:48:58 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memcpy(void *destination, const void *source, size_t num)
{
	unsigned char	*src;
	unsigned char	*dest;

	src = (unsigned char *) source;
	dest = (unsigned char *) destination;
	if (src == NULL && dest == NULL)
		return (destination);
	while (num--)
		*dest++ = *src++;
	return (destination);
}
