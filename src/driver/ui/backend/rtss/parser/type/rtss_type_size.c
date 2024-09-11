/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtss_type_size.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bonsthie <bonsthie@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 16:59:58 by bonsthie          #+#    #+#             */
/*   Updated: 2024/09/10 15:57:56 by bonsthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rtss_parse.h"
#include "libft.h"

void	rtss_type_width(t_htab *tab, t_hentry *entry, char *value)
{
	hentry_add_spec(tab, entry, (t_keyw)WIDTH, ft_atoi(value));
}

void	rtss_type_height(t_htab *tab, t_hentry *entry, char *value)
{
	hentry_add_spec(tab, entry, (t_keyw)HEIGHT, ft_atoi(value));
}
