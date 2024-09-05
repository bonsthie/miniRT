/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtss_lexer_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bonsthie <bonsthie@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 19:35:38 by bonsthie          #+#    #+#             */
/*   Updated: 2024/09/05 00:39:55 by bonsthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <stdbool.h>

bool	rtss_is_empty(char *str)
{
	while (*str)
	{
		if (!ft_strchr(" \t\n", *str))
			break ;
		str++;
	}
	return (*str == 0);
}

int	is_name_char(int c)
{
	return (ft_isalpha(c) || c == '.');
}

int	is_name_char_attr(int c)
{
	return (ft_isalpha(c) || c == '-');
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

char	*rtss_get_attr_name(const char **str)
{
	char	name[1024];
	char	*name_ptr;

	while (**str && !is_name_char(**str))
		(*str)++;
	name_ptr = name;
	while (**str && is_name_char_attr(**str))
		*name_ptr++ = *((*str)++);
	*name_ptr = 0;
	return (ft_strdup(name));
}

char	**fuck_norminette(void)
{
	static char	*norminette_is_a_slut[] = (char *[]){"width", "height",
			"min-width", "max-width", "min-height", "max-height", "padding",
			"padding-left", "padding-right", "padding-bottom", "padding-top",
			"margin", "margin-left", "margin-right", "margin-bottom",
			"margin-top", "border", "border-width", "border-style",
			"border-color", "border-top", "border-top-width",
			"border-top-style", "border-top-color", "border-right",
			"border-right-width", "border-right-style", "border-right-color",
			"border-bottom", "border-bottom-width", "border-bottom-style",
			"border-bottom-color", "border-left", "border-left-width",
			"border-left-color", "border-radius", "border-top-left-radius",
			"border-top-right-radius", "border-bottom-right-radius",
			"border-bottom-left-radius", "background-color",
			"background-color-however", "background-color-clicked", NULL};
	return (norminette_is_a_slut);
}
