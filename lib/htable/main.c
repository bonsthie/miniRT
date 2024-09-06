// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   main.c                                             :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: rgramati <rgramati@student.42angouleme.fr  +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2024/08/29 13:39:05 by rgramati          #+#    #+#             //
//   Updated: 2024/08/31 15:35:41 by rgramati         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include <stdint.h>
#include <stdio.h>

#include "include/htab.h"

#define SIZE(X) printf("sizeof(%s) = [%zu]\n", #X, sizeof(X));

#define DEBUG_HEADER(T, X) {printf("[DEBUG] <%p> %s %s\n", X, #T, #X); printf("{\n");}

static void	debug_pchunk(t_pchunk *chunk)
{
	DEBUG_HEADER(t_pchunk *, chunk);
	while (chunk)
	{
		for (size_t i = 0; i < chunk->capacity; i++)
		{
			if (!(i % 6))
				printf("|\n\t");
			if (i < chunk->size)
				printf("|[%2lu] %12lu", i, chunk->data[i]);
			else
				printf("|[%2lu] %12lu", i, 0UL);
		}
		chunk = chunk->next;
	}
	printf("|\n}\n");
}

static void debug_hentry(t_hentry *entry)
{
	DEBUG_HEADER(t_hentry *, entry);
	printf("\tids   : ");
	for (int i = 0; i < 8; i++)
	{
		printf("%d:%d", entry->ids[i].id2, entry->ids[i].id1);
		if (i < 7)
			printf(":");
	}
	printf("\n");
	printf("\tkey   : %s\n", entry->key);
	printf("\tindex : %zu\n", entry->index);
	printf("\tsize  : %zu\n", entry->size);
	printf("}\n");
}

static void debug_htab(t_htab *tab)
{
	t_pchunk	*tmp;

	DEBUG_HEADER(t_htab *, tab)
	for (int i = 0; i < HTAB_BASE_SIZE; i++)
		debug_hentry(&tab->table[i]);
	tmp = tab->params;
	while (tmp)
	{
		debug_pchunk(tmp);
		tmp = tmp->next;
	}
}

int	main(void)
{
	t_htab	tab;

	htab_new(&tab);

	t_hentry	*test = htab_add(&tab, "coucou");

	hentry_add_spec(&tab, test, DUMMY1, 42);
	hentry_add_spec(&tab, test, DUMMY2, 69);

	debug_htab(&tab);

	htab_del(&tab);

	return (0);
}
