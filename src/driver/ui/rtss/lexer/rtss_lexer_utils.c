/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtss_lexer_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bonsthie <bonsthie@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 19:35:38 by bonsthie          #+#    #+#             */
/*   Updated: 2024/09/04 19:45:26 by bonsthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <libft.h>

bool rtss_is_empty(char *str)
{
	while (*str)
	{
		if (!ft_strchr(" \t\n", *str))
			break;
		str++;
	}
	return (*str == 0);
}

int	is_name_char(int c)
{
	return (ft_isalpha(c) || c == '.');
}

char	*rtss_get_name(const char **str)
{
	char	name[1024];
	char	*name_ptr;
	char	*end_name;

	end_name = ft_strchr(*str, '{');
	if (!end_name)
		return (NULL);
	while (**str && !is_name_char(**str))
		(*str)++;
	name_ptr = name;
	while (**str && is_name_char(**str))
		*name_ptr++ = *((*str)++);
	*name_ptr = 0;
	*str = end_name + 1;
	return (ft_strdup(name));
}
