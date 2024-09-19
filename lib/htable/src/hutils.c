/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hutils.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgramati <rgramati@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 15:16:37 by rgramati          #+#    #+#             */
/*   Updated: 2024/08/31 15:22:13 by rgramati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdint.h>

size_t	h_strlen(const char *str)
{
	const char	*tmp;

	tmp = str;
	while (*tmp)
		tmp++;
	return (tmp - str);
}

size_t	h_longlen(const char *str)
{
	const char *tmp;

	tmp = str;
	while ((tmp - str) < 8 && *tmp)
		tmp++;
	return (tmp - str);
}

char	*h_strdup(const char *str)
{
	char	*cpy;
	char	*tmp;

	cpy = malloc(h_strlen(str) + 1);
	if (cpy)
	{
		tmp = cpy;
		while (*str)
			*tmp++ = *str++;
		*tmp = 0;
	}
	return (cpy);
}

int	h_strcmp(const char *s1, const char *s2)
{
	if (!s1 || !s2)
		return (s1 != s2);
	while (*s1 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}
