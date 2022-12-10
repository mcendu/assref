/* SPDX-License-Identifier: MIT
 * Copyright (C) 2022 McEndu et al.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice
 * (including the next paragraph) shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
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

typedef unsigned (*aref_hashfunc)(void *key);

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

#ifdef __cplusplus
}
#endif

#endif /* !_AREF__TABLE_H */
