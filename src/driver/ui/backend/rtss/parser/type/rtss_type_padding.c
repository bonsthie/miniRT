/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtss_type_padding.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bonsthie <bonsthie@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 21:12:17 by bonsthie          #+#    #+#             */
/*   Updated: 2024/09/10 15:58:42 by bonsthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rtss_parse.h"
#include "__rtss_type.h"
#include "htab.h"
#include <stdint.h>

void	rtss_type_padding(t_htab *tab, t_hentry *entry, char *value)
{
	hentry_add_spec(tab, entry, (t_keyw)PADDING, __rtss_bit_packing(&value));
}

void	rtss_type_padding_left(t_htab *tab, t_hentry *entry, char *value)
{
	uint64_t	base;

	// no entry return (0 change in htab);
	base = hentry_get_spec(tab, entry, (t_keyw)PADDING);
	hentry_add_spec(tab, entry, (t_keyw)PADDING, __rtss_bit_packing_1(&value,
			base));
}

void	rtss_type_padding_bottom(t_htab *tab, t_hentry *entry, char *value)
{
	uint64_t	base;

	base = hentry_get_spec(tab, entry, (t_keyw)PADDING);
	hentry_add_spec(tab, entry, (t_keyw)PADDING, __rtss_bit_packing_2(&value,
			base));
}

void	rtss_type_padding_right(t_htab *tab, t_hentry *entry, char *value)
{
	uint64_t	base;

	base = hentry_get_spec(tab, entry, (t_keyw)PADDING);
	hentry_add_spec(tab, entry, (t_keyw)PADDING, __rtss_bit_packing_3(&value,
			base));
}

void	rtss_type_padding_top(t_htab *tab, t_hentry *entry, char *value)
{
	uint64_t	base;

	base = hentry_get_spec(tab, entry, (t_keyw)PADDING);
	hentry_add_spec(tab, entry, (t_keyw)PADDING, __rtss_bit_packing_4(&value,
			base));
}
