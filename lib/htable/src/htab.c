/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   htab.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgramati <rgramati@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 13:33:24 by rgramati          #+#    #+#             */
/*   Updated: 2024/08/31 15:09:45 by rgramati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include <htab.h>

uint32_t	htab_hash(const unsigned char *key)
{
	uint32_t	h;

	h = 5381;
	while (*key)
		h = ((h << 5) + h) + *key++;
	return (h);
}

void	htab_new(t_htab *h)
{
	*h = (t_htab){0};
	h->params = pchunk_new();
}

void	htab_del(t_htab *h)
{
	pchunk_del(h->params);
}

t_hentry	*htab_add(t_htab *h, const char *key)
{
	uint32_t	index;
	t_hentry	*entry;

	index = htab_hash((unsigned char *)key) % HTAB_BASE_SIZE;
	entry = &h->table[index];
	while (index < HTAB_BASE_SIZE && entry->size != 0)
	{
		index++;
		entry = &h->table[index];
	}
	*entry = (t_hentry){0};
	entry->key = h_strdup(key);
	hentry_init(h, entry);
	return (entry);
}

t_hentry	*htab_get(t_htab *h, const char *key)
{
	uint32_t	index;
	t_hentry	*entry;

	index = htab_hash((unsigned char *)key) % HTAB_BASE_SIZE;
	entry = &h->table[index];
	while (index < HTAB_BASE_SIZE && h_strcmp(entry->key, key))
	{
		index++;
		entry = &h->table[index];
	}
	if (index == HTAB_BASE_SIZE)
		return (NULL);
	if (h_strcmp(entry->key, key))
		return (NULL);
	return (entry);
}
