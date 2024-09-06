/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pchunk.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgramati <rgramati@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 14:30:23 by rgramati          #+#    #+#             */
/*   Updated: 2024/08/31 14:47:42 by rgramati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <stdlib.h>

#include <htab.h>

t_pchunk	*pchunk_new(void)
{
	t_pchunk	*new;
	uint32_t	i;

	new = malloc(sizeof(t_pchunk));
	{
		new->next = NULL;
		new->size = 0;
		new->capacity = PCHUNK_BASE_SIZE;
		i = 0;
		while (i < PCHUNK_BASE_SIZE)
			new->data[i++] = 0;
	}
	return (new);
}

void	pchunk_del(t_pchunk *chunk)
{
	t_pchunk	*next;

	while (chunk->next)
	{
		next = chunk->next;
		free(chunk);
		chunk = next;
	}
	free(chunk);
}

uint64_t	*pchunk_val_alloc(t_pchunk *chunk)
{
	uint64_t	*ptr;	

	if (!chunk)
		return (NULL);
	while (chunk->next && chunk->size == chunk->capacity)
		chunk = chunk->next;
	if (chunk->size == chunk->capacity)
	{
		chunk->next = pchunk_new();
		chunk = chunk->next;
	}
	ptr = &chunk->data[chunk->size];
	chunk->size++;
	return (ptr);
}

void	pchunk_val_push(t_pchunk *chunk, uint64_t value)
{
	uint64_t	*ptr;

	ptr = pchunk_val_alloc(chunk);
	if (!ptr)
		return ;
	*ptr = value;
}

void	pchunk_val_free(t_pchunk *chunk)
{
	if (!chunk)
		return ;
	while (chunk->next)
		chunk = chunk->next;
	chunk->size--;
	chunk->data[chunk->size] = 0;
}
