/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtss_class_to_hentry.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bonsthie <bonsthie@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 17:27:08 by bonsthie          #+#    #+#             */
/*   Updated: 2024/09/09 23:21:18 by bonsthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtss_parse.h"
#include <stdio.h>
#include <htab.h>

void rtss_class_to_hentry(t_htab *tab, struct s_rtss_lex_class *class)
{
	t_hentry *entry;

	entry = htab_add(tab, class->name);
	printf("class name [%s]\n", class->name);
	rtss_attr_to_hentry_spec(class->attr, tab, entry);
	printf("class name [%s] end\n", class->name);
}
