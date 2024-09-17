/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtss_type_background_color.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bonsthie <bonsthie@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 17:08:41 by bonsthie          #+#    #+#             */
/*   Updated: 2024/09/17 13:35:18 by bonsthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rtss_parse.h"
#include "__rtss_type.h"
#include "htab.h"

void	rtss_type_background_color(t_htab *tab, t_hentry *entry, char *value)
{
	hentry_add_spec(tab, entry, (t_keyw)BACKGROUND_COLOR,
		__rtss_type_color(value));
}

void	rtss_type_background_color_however(t_htab *tab, t_hentry *entry,
		char *value)
{
	hentry_add_spec(tab, entry, (t_keyw)BACKGROUND_COLOR_HOWEVER,
		__rtss_type_color(value));
}

void	rtss_type_background_color_click(t_htab *tab, t_hentry *entry,
		char *value)
{
	hentry_add_spec(tab, entry, (t_keyw)BACKGROUND_COLOR_CLIKED,
		__rtss_type_color(value));
}
