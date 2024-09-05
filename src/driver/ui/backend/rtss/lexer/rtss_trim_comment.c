/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtss_trim_comment.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bonsthie <bonsthie@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 11:30:50 by bonsthie          #+#    #+#             */
/*   Updated: 2024/09/04 17:09:37 by bonsthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "rtss_lexer.h"
#include <stdbool.h>
#include <stdio.h>

static	char *__rtss_allocate_clean_file(const char *file)
{
	char *clean_file;

	clean_file = malloc(ft_strlen(file) * sizeof(char));
	if (!clean_file)
		ft_putstr_fd("RTSS Error: cannot allocate memory for the comment clean file\n", 2);
	return (clean_file);
}

static bool __rtss_in_comment(const char *file)
{
	static bool in_comment = false;
	static char last_char = 0;

	if (in_comment)
	{
		if (*file == '/' && last_char == '*')
		{
			in_comment = false;
		}
		last_char = *file;
		return (true);
	}
	if (!in_comment && *file == '/' && *(file + 1) == '*')
	{
		in_comment = true;
		last_char = *file;
		return (true);
	}
	last_char = *file;
	return (false);
}

static void __rtss_trim_comment(char *dest, const char *src)
{
	while (*src)
	{
		if (!__rtss_in_comment(src))
			*dest++ = *src;
		src++;
	}
	*dest = 0;
}

char *rtss_trim_comment(char *file)
{
	char *clean_file;

	clean_file = __rtss_allocate_clean_file(file);
	if (!clean_file)
		return (NULL);
	__rtss_trim_comment(clean_file, file);
	free(file);
	return (clean_file);
}
