/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtss_border.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bonsthie <bonsthie@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 19:32:59 by bonsthie          #+#    #+#             */
/*   Updated: 2024/09/17 19:34:16 by bonsthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rtss_parse.h"
#include "__rtss_type.h"
#include "htab.h"
#include "libft.h"

void	rtss_type_border_color(t_htab *tab, t_hentry *entry, char *value)
{
	hentry_add_spec(tab, entry, (t_keyw)BORDER_COLOR,
		__rtss_type_color(value));
}
void	rtss_type_border_size(t_htab *tab, t_hentry *entry, char *value)
{
	hentry_add_spec(tab, entry, (t_keyw)BORDER_SIZE, ft_strtoll(value, NULL, 10));
}
