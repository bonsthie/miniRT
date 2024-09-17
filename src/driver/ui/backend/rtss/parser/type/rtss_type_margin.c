/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtss_type_margin.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bonsthie <bonsthie@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 20:51:46 by bonsthie          #+#    #+#             */
/*   Updated: 2024/09/17 14:57:25 by bonsthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rtss_parse.h"
#include "__rtss_type.h"
#include "htab.h"
#include <stdint.h>

#include <stdio.h>
void	rtss_type_margin(t_htab *tab, t_hentry *entry, char *value)
{
	hentry_add_spec(tab, entry, (t_keyw)MARGIN, __rtss_bit_packing(&value));
}

void	rtss_type_margin_left(t_htab *tab, t_hentry *entry, char *value)
{
	uint64_t	base;

	// no entry return (0 change in htab);
	base = hentry_get_spec(tab, entry, (t_keyw)MARGIN);
	hentry_add_spec(tab, entry, (t_keyw)MARGIN, __rtss_bit_packing_1(&value,
			base));
}

void	rtss_type_margin_bottom(t_htab *tab, t_hentry *entry, char *value)
{
	uint64_t	base;

	base = hentry_get_spec(tab, entry, (t_keyw)MARGIN);
	hentry_add_spec(tab, entry, (t_keyw)MARGIN, __rtss_bit_packing_2(&value,
			base));
}

void	rtss_type_margin_right(t_htab *tab, t_hentry *entry, char *value)
{
	uint64_t	base;

	base = hentry_get_spec(tab, entry, (t_keyw)MARGIN);
	hentry_add_spec(tab, entry, (t_keyw)MARGIN, __rtss_bit_packing_3(&value,
			base));
}

void	rtss_type_margin_top(t_htab *tab, t_hentry *entry, char *value)
{
	uint64_t	base;

	base = hentry_get_spec(tab, entry, (t_keyw)MARGIN);
	hentry_add_spec(tab, entry, (t_keyw)MARGIN, __rtss_bit_packing_4(&value,
			base));
}
