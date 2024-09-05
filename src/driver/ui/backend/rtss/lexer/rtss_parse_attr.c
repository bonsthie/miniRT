/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtss_parse_attr.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bonsthie <bonsthie@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 17:09:10 by bonsthie          #+#    #+#             */
/*   Updated: 2024/09/05 14:59:17 by bonsthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "rtss_lexer.h"
#include <stdbool.h>
#include <stdio.h>

enum e_rtss_lex_attr_type	__rtss_find_type(char **str)
{
	char	*end_type;
	char	*type;
	int		i;
	char	**type_attr;

	end_type = ft_strchr(*str, ':');
	if (!end_type)
	{
		ft_putstr_fd("RTSS Error: invalid attribute missing ':'\n", 2);
		return (0);
	}
	type = rtss_get_attr_name((const char **)str);
	if (!type)
		return (0);
	i = 0;
	type_attr = fuck_norminette();
	while (type_attr[i] && ft_strcmp(type, type_attr[i]))
		i++;
	free(type);
	*str = end_type + 1;
	return (i);
}

static struct s_rtss_lex_attr	*__rtss_create_attr(char *str)
{
	struct s_rtss_lex_attr	*new;

	new = malloc(sizeof(struct s_rtss_lex_attr));
	if (!new)
		return (NULL);
	new->type = __rtss_find_type(&str);
	new->value = ft_strdup(str);
	if (new->value)
		return (new);
	free(new);
	return (NULL);
}

static struct s_rtss_lex_attr	*__rtss_split_to_attr(char **str)
{
	struct s_rtss_lex_attr	*head;
	struct s_rtss_lex_attr	*attr;
	struct s_rtss_lex_attr	*new_attr;

	head = NULL;
	while (*str)
	{
		if (rtss_is_empty(*str))
			break ;
		new_attr = __rtss_create_attr(*str);
		if (!new_attr)
			break ;
		if (!head)
		{
			head = new_attr;
			attr = head;
		}
		else
		{
			attr->next = new_attr;
			attr = attr->next;
		}
		str++;
	}
	return (head);
}

static struct s_rtss_lex_attr	*__rtss_parse_attr(char *str)
{
	char	**split_args;
	struct s_rtss_lex_attr *attr;

	split_args = ft_split(str, ';');
	if (!split_args)
	{
		ft_putstr_fd("RTSS Error: malloc error while spliting attr\n", 2);
		return (NULL);
	}
	attr = __rtss_split_to_attr(split_args);
	free_strs(split_args);
	return (attr);
}

struct s_rtss_lex_attr	*rtss_parse_attr(char **str)
{
	struct s_rtss_lex_attr	*new;
	char					*str_end;

	str_end = ft_strchr(*str, '}');
	if (!str_end)
	{
		ft_putstr_fd("RTSS Error: parsing file missing '}'\n", 2);
		return (NULL);
	}
	*str_end = 0;
	new = __rtss_parse_attr(*str);
	*str = str_end + 1;
	return (new);
}
