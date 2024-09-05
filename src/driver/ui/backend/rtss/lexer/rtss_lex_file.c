/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtss_lex_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bonsthie <bonsthie@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 12:37:17 by bonsthie          #+#    #+#             */
/*   Updated: 2024/09/04 18:31:13 by bonsthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtss_lexer.h"
#include <stdlib.h>

struct s_rtss_lex_file rtss_lex_file(const char *file)
{
	struct s_rtss_lex_file lex_file;
	struct s_rtss_lex_class	*class;
	struct s_rtss_lex_class	*new_attr;

	lex_file.head = NULL;
	while (*file)
	{
		new_attr = rtss_create_class(&file);
		if (!new_attr)
			return (lex_file);
		if (!lex_file.head)
		{
			lex_file.head = new_attr;
			class = lex_file.head;
		}
		else
		{
			class->next = new_attr;
			class = class->next;
		}
	}
	return (lex_file);
}
