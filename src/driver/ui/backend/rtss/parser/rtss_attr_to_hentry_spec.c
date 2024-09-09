/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtss_attr_to_hentry_spec.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bonsthie <bonsthie@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 17:34:03 by bonsthie          #+#    #+#             */
/*   Updated: 2024/09/09 23:29:36 by bonsthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "htab.h"
#include "rtss_parse.h"
#include <stdio.h>


void rtss_attr_to_hentry_spec(struct s_rtss_lex_attr *attr, t_htab *tab, t_hentry *entry)
{
	void **func;
	
	func = rtss_parser_function();
	char **name = fuck_norminette();
	while(attr)
	{
		if (attr->type < NULL_ARG)
		{
			printf("\t%s %d %p\n", name[attr->type], attr->type, entry);
			((t_rtss_parse_func *)func[attr->type])(tab, entry, attr->value); 
		}
		attr = attr->next;
	}
}
