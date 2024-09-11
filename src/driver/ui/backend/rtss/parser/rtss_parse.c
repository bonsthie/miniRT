/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtss_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bonsthie <bonsthie@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 16:48:47 by bonsthie          #+#    #+#             */
/*   Updated: 2024/09/10 15:57:56 by bonsthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "rtss_parse.h"
#include <htab.h>

static t_htab	*__rtss_alloc_htab(void)
{
	t_htab	*tab;

	tab = malloc(sizeof(t_htab));
	if (!tab)
	{
		ft_putstr_fd("RTSS Error: faild to allocate for the css hash table\n",
			2);
		return (NULL);
	}
	htab_new(tab);
	return (tab);
}

t_htab	*rtss_parse(struct s_rtss_lex_file file)
{
	t_htab					*tab;
	struct s_rtss_lex_class	*class;

	tab = __rtss_alloc_htab();
	if (!tab)
		return (NULL);
	class = file.head;
	while (class)
	{
		rtss_class_to_hentry(tab, class);
		class = class->next;
	}
	return (tab);
}
