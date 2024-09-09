/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtss_type_border_radius.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bonsthie <bonsthie@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 21:12:49 by bonsthie          #+#    #+#             */
/*   Updated: 2024/09/09 22:46:41 by bonsthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "__rtss_type.h"
#include "../rtss_parse.h"
#include "htab.h"
#include <stdint.h>

void rtss_type_border_radius(t_htab *tab, t_hentry *entry, char *value)
{
	hentry_add_spec(tab, entry, (t_keyw)BORDER_RADIUS, __rtss_bit_packing(&value));
}

void rtss_type_border_radius_top_left(t_htab *tab, t_hentry *entry, char *value)
{
	uint64_t base;

	// no entry return 0 change in htab;
	base = hentry_get_spec(tab, entry, (t_keyw)BORDER_RADIUS);
	hentry_add_spec(tab, entry, (t_keyw)BORDER_RADIUS, __rtss_bit_packing_1(&value, base));
}

void rtss_type_border_radius_top_right(t_htab *tab, t_hentry *entry, char *value)
{
	uint64_t base;

	base = hentry_get_spec(tab, entry, (t_keyw)BORDER_RADIUS);
	hentry_add_spec(tab, entry, (t_keyw)BORDER_RADIUS, __rtss_bit_packing_2(&value, base));
}
void rtss_type_border_radius_bottom_right(t_htab *tab, t_hentry *entry, char *value)
{
	uint64_t base;

	base = hentry_get_spec(tab, entry, (t_keyw)BORDER_RADIUS);
	hentry_add_spec(tab, entry, (t_keyw)BORDER_RADIUS, __rtss_bit_packing_3(&value, base));
}

void rtss_type_border_radius_bottom_left(t_htab *tab, t_hentry *entry, char *value)
{
	uint64_t base;

	base = hentry_get_spec(tab, entry, (t_keyw)BORDER_RADIUS);
	hentry_add_spec(tab, entry, (t_keyw)BORDER_RADIUS, __rtss_bit_packing_4(&value, base));
}
