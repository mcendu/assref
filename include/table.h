/*
 * SPDX-License-Identifier: GPL-2.0-or-later
 * Copyright (C) 2022 McEndu et al.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, see <https://www.gnu.org/licenses/>.
 *
 */

/**
 * @brief Hash table implementation.
 *
 * This header contains an API for a hash table implementation that can
 * index arbitrary data.
 */
#ifndef _AREF__TABLE_H
#define _AREF__TABLE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>

struct aref_tableentry {
	unsigned hash;
	size_t poolindex;
	void *data;
	struct aref_tableentry *cdr;
};

typedef unsigned (*aref_hashfunc)(const void *key);

typedef struct {
	aref_hashfunc hashfunc;
	struct aref_tableentry *pool;
	size_t size;
	size_t capacity;
	struct aref_tableentry *table[256];
} aref_table;

/**
 * @brief Initialize a table.
 *
 * @param h The table to initialize. Must point to allocated memory.
 * @param f The hash function to use.
 */
extern void aref_inittable(aref_table *h, aref_hashfunc f);
/**
 * @brief Insert data.
 *
 * @param key The key associated with the data.
 * @param data The data.
 */
extern void aref_table_insert(aref_table *h, void *key, void *data);
/**
 * @brief Find an entry.
 *
 * @param key The key to index.
 * @return A pointer to the specified entry, or NULL if it does not exist.
 */
extern void *aref_table_find(aref_table *h, void *key);
/**
 * @brief Delete an entry.
 *
 * @param key The key to delete.
 * @return A pointer to the deleted entry. The caller has to manually free it.
 */
extern void *aref_table_delete(aref_table *h, void *key);
/**
 * @brief Free all data associated with the table.
 */
extern void aref_freetable(aref_table *h);

/**
 * @brief djb2a hash algorithm.
 *
 * @param data Arbitrary data to hash.
 * @param size The size of the data.
 * @return The hash.
 */
extern unsigned aref_djb2a(const void *data, size_t size);
/**
 * @brief Gets the hash of a string.
 *
 * @param data The string to be hashed.
 * @return The hash.
 */
extern unsigned aref_hash_string(const void *data);
/**
 * @brief Gets the case-insensitive hash of a string.
 *
 * @param data The string to be hashed.
 * @return The hash.
 */
extern unsigned aref_cihash_string(const void *data);

#ifdef __cplusplus
}
#endif

#endif /* !_AREF__TABLE_H */
