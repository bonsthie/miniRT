/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 18:35:22 by bbonnet           #+#    #+#             */
/*   Updated: 2024/07/18 13:48:59 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strcpy(char *dest, char *src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_realloc_str(char *str, size_t new_size)
{
	void	*new_ptr;

	if (new_size == 0)
	{
		free(str);
		return (NULL);
	}
	if (!str)
		return (malloc(new_size * sizeof(char)));
	new_ptr = malloc(new_size);
	if (new_ptr)
	{
		ft_strcpy(new_ptr, str);
		free(str);
	}
	return (new_ptr);
}
