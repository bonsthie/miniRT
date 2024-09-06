/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hentry.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgramati <rgramati@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 16:18:20 by rgramati          #+#    #+#             */
/*   Updated: 2024/08/31 15:10:01 by rgramati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>

#include <htab.h>

void	hentry_init(t_htab *h, t_hentry *entry)
{
	t_pchunk	*chunk;
	uint32_t	offset;

	chunk = h->params;
	offset = 0;
	while (chunk->next)
	{
		offset += PCHUNK_BASE_SIZE;
		chunk = chunk->next;
	}
	offset += chunk->size;
	entry->index = offset;
	entry->size = 0;
	*(uint64_t *)&entry->ids = 0;
}

void	hentry_add_spec(t_htab *h, t_hentry *entry, t_keyw k, uint64_t val)
{
	uint64_t	ids;
	uint64_t	mask;
	uint64_t	new;

	if (entry->size == 8)
		return ;
	ids = *(uint64_t *)&entry->ids;
	mask = 0xF0UL;
	new = (uint64_t)k * 0x1111111111111111;
	while (mask)
	{
		if (!(mask & ids) || (mask & ids) == k)
			break ;
		mask >>= 4;
		if (!(mask & ids) || (mask & ids) == k)
			break ;
		mask <<= 12;
	}
	if (!mask || (mask & ids) == k)
		return ;
	*(uint64_t *)&entry->ids |= (new & mask);
	pchunk_val_push(h->params, val);
	entry->size++;
	ids = *(uint64_t *)&entry->ids;
}

uint64_t	hentry_get_spec(t_htab *h, t_hentry *entry, t_keyw k)
{
	uint64_t	ids;
	uint64_t	mask;
	uint64_t	off;

	if (entry->size == 8)
		return (-1);
	ids = *(uint64_t *)&entry->ids;
	mask = 0xF0UL;
	off = 0;
	while (mask)
	{
		if ((mask & ids) == k)
			break ;
		mask >>= 4;
		off++;
		if ((mask & ids) == k)
			break ;
		mask <<= 12;
		off++;
	}
	if (!mask)
		return (-1);
	return (h->params->data[entry->index + off]);
}
