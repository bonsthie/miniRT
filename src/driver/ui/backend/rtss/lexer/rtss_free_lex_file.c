/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtss_free_lex_file.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bonsthie <bonsthie@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 15:52:50 by bonsthie          #+#    #+#             */
/*   Updated: 2024/09/11 16:04:57 by bonsthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtss_lexer.h"
#include <stdlib.h>

static void __rtss_free_lex_attr(struct s_rtss_lex_attr *attr)
{
	struct s_rtss_lex_attr *tmp;

	while (attr)
	{
		free(attr->value);
		tmp = attr->next;
		free(attr);
		attr = tmp;
	}
}

void rtss_free_lex_file(struct s_rtss_lex_file file)
{
	struct s_rtss_lex_class *class;

	class = file.head;
	while (class)
	{
		__rtss_free_lex_attr(class->attr);
		free(class->name);
		file.head = class->next;
		free(class);
		class = file.head;
	}

}
