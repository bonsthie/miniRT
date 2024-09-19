/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hentry.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgramati <rgramati@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 16:18:20 by rgramati          #+#    #+#             */
/*   Updated: 2024/09/19 17:35:39 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <emmintrin.h>
#include <htab.h>
#include <immintrin.h>
#include <stdint.h>
#include <unistd.h>

void	hentry_init(t_htab *h, t_hentry *entry, char *key)
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
	entry->key = key;
	*(uint64_t *)&entry->ids = 0;
}

void	hentry_add_spec(t_htab *h, t_hentry *entry, t_keyw k, uint64_t val)
{
	size_t	index;
	__v16qi	ids;
	__v16qi	mask_k;

	mask_k = _mm_set1_epi8(k);
	ids = _mm_loadu_si128((const __m128i *)entry->ids);
	index = _mm_movemask_epi8(ids == mask_k);
	if (index)
	{
		index = __builtin_ctz(index) + entry->index;
		h->params->data[index] = val;
		return ;
	}
	mask_k = _mm_set1_epi8(0);
	index = _mm_movemask_epi8(ids == mask_k);
	if (!index)
		return ;
	entry->ids[__builtin_ctz(index)] = k;
	pchunk_val_push(h->params, val);
	entry->size++;
}

uint64_t	hentry_get_spec(t_htab *h, t_hentry *entry, t_keyw k)
{
	size_t	index;
	__v16qi		ids;
	__v16qi		mask_k;

	mask_k = _mm_set1_epi8(k);
	ids = _mm_loadu_si128((const __m128i *)entry->ids);
	index = _mm_movemask_epi8(ids == mask_k);
	if (index == 0)
		return (-1);
	index = __builtin_ctz(index) + entry->index;
	return (h->params->data[index]);
}
