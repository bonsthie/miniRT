/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtss_create_class.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bonsthie <bonsthie@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 16:00:48 by bonsthie          #+#    #+#             */
/*   Updated: 2024/09/04 19:44:54 by bonsthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "rtss_lexer.h"
#include <stdio.h>
#include <stdlib.h>

static struct s_rtss_lex_class	*__rtss_alloc_class(void)
{
	struct s_rtss_lex_class	*new;

	new = malloc(sizeof(struct s_rtss_lex_class));
	if (!new)
		ft_putstr_fd("RTSS Error: fail allocate class struct", 2);
	return (new);
}

struct s_rtss_lex_class	*rtss_create_class(const char **str)
{
	struct s_rtss_lex_class	*new;

	new = __rtss_alloc_class();
	if (!new)
		return (NULL);
	new->name = rtss_get_name(str);
	if (!new->name)
	{
		free(new);
		return (NULL);
	}
	printf("name %s\n", new->name);
	new->attr = rtss_parse_attr((char **)str);
	new->next = NULL;
	return (new);
}
