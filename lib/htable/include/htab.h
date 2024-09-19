/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   htab.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgramati <rgramati@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 13:07:03 by rgramati          #+#    #+#             */
/*   Updated: 2024/09/19 16:54:33 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTAB_H
# define HTAB_H

# include <unistd.h>
# include <stdint.h>

# define PCHUNK_BASE_SIZE 30

size_t		h_strlen(const char *str);

size_t		h_longlen(const char *str);

char		*h_strdup(const char *str);

int			h_strcmp(const char *s1, const char *s2);

/* ************************************************************************** */

typedef struct s_htab		t_htab;
typedef struct s_pchunk		t_pchunk;
typedef struct s_htab_entry	t_hentry;
typedef enum e_rtss_keyword	t_keyw;

/* ************************************************************************** */

struct	s_pchunk
{
	uint32_t	size;
	uint32_t	capacity;
	t_pchunk	*next;
	uint64_t	data[PCHUNK_BASE_SIZE];
};

/**
 * @brief		Initializes a t_pchunk for the hash table.
 *
 * @returns		A pointer to a newly allocated pchunk.
 */
t_pchunk	*pchunk_new(void);

/**
 * @brief		Deletes a list of t_pchunk.
 *
 * @param		chunk	The actual chunk to free.
 */
void		pchunk_del(t_pchunk *chunk);

/**
 * @brief		"Allocate" space for a new value into a chunk
 *
 * @param		chunk	The actual chunk where the value has to be stored.
 *
 * @returns		The address of the next free spot in the actual chunk.
 * @note		Will call pchunk_new() if there is no more room in 
 *				the actual chunk.
 */
uint64_t	*pchunk_val_alloc(t_pchunk *chunk);

/**
 * @brief		"Free" the last value spot in the actual chunk.
 *
 * @param		chunk	The actual chunk where the value has to be freed.
 */
void		pchunk_val_free(t_pchunk *chunk);

/**
 * @brief		Push a value into a chunk.
 *
 * @param		chunk	The actual chunk where the value has to be pushed
 * @param		value	The value.
 *
 * @note		Will call pchunk_val_alloc(chunk) to get the address, then
 *				stores the value at that place.
 */
void		pchunk_val_push(t_pchunk *chunk, uint64_t value);

/* ************************************************************************** */

enum	e_rtss_keyword
{
	DUMMY1 = 1,
	DUMMY2 = 2,
	DUMMY3 = 3,
	DUMMY4 = 4
};

struct	s_htab_entry
{
	char		ids[16];
	char		*key;
	uint64_t	index;
	uint64_t	size;
};

/**
 * @brief		Initializes a new t_hentry for the hash table.
 *
 * @param		h		The hash table.
 * @param		entry	The actual entry to init.
 * @param		key		Entry key.
 *
 * @note		This function should be used to set the start index
 *				of every new entry.
 */
void		hentry_init(t_htab *h, t_hentry *entry, char *key);

/**
 * @brief		Adds a parameter to an hentry.
 *
 * @param		h		The hash table
 * @param		entry	The entry where the value has to be added.
 * @param		k		Parameter keyword
 * @param		val		The corresponding value.
 *
 * @note		Will use pchunk_val_push() to set the new value.
 */
void		hentry_add_spec(t_htab *h, t_hentry *entry, t_keyw k, uint64_t val);

/**
 * @brief		Get a parameter from an entry.
 *
 * @param		h		The hash table.
 * @param		entry	The entry where the value has to be searched for.
 * @param		k		Parameter keyword
 *
 * @returns		The actual value corresponding to keyword 'k' in the entry
 */
uint64_t	hentry_get_spec(t_htab *h, t_hentry *entry, t_keyw k);

/* ************************************************************************** */

# define HTAB_BASE_SIZE	32

struct	s_htab
{
	t_hentry	table[HTAB_BASE_SIZE];
	t_pchunk	*params;
	uint32_t	size;
};

/**
 * @brief		Hash function for the hash table.
 *
 * @param		key		Key string.
 *
 * @returns		Hash computed from the key string.
 *
 * @note		This function is an implementation of djb2 hash.
 */
uint32_t	htab_hash(const unsigned char *key);

/**
 * @brief		Initializes a new hash table.
 *
 * @param		h		The hash table to init.
 */
void		htab_new(t_htab *h);

/**
 * @brief		Deletes a hash table.
 *
 * @param		h		The hash table to delete.
 */
void		htab_del(t_htab *h);

/**
 * @brief		Add a t_hentry to the hash table based on key.
 *
 * @param		h		The hash table.
 * @param		key		Key string.
 *
 * @returns		A t_hentry pointer to this new entry.
 */
t_hentry	*htab_add(t_htab *h, const char *key);

/**
 * @brief		Get a t_hentry from the hash table based on key.
 *
 * @param		h		The hash table.
 * @param		key		Key string.
 *
 * @returns		A t_hentry pointer where entry->key == key.
 */
t_hentry	*htab_get(t_htab *h, const char *key);

#endif
