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

#include <table.h>

#include <ctype.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define ALLOCATION_UNIT 128

void aref_inittable(aref_table *h, aref_hashfunc f)
{
	h->hashfunc = f;
	h->pool = malloc(ALLOCATION_UNIT * sizeof(struct aref_tableentry));
	memset(h->table, 0, 256 * sizeof(void *));
	h->size = 0;
	h->capacity = ALLOCATION_UNIT;
}

void aref_freetable(aref_table *h)
{
	free(h->pool);
	h->pool = NULL;
}

void aref_table_insert(aref_table *h, void *key, void *data)
{
	h->size += 1;
	if (h->size == h->capacity) {
		h->capacity += ALLOCATION_UNIT;
		h->pool
			= realloc(h->pool, h->capacity * sizeof(struct aref_tableentry));
	}

	struct aref_tableentry *entry = h->pool + h->size - 1;
	entry->poolindex = h->size - 1;
	entry->cdr = NULL;
	entry->hash = h->hashfunc(key);
	entry->data = data;

	struct aref_tableentry **insertloc = h->table + (uint8_t)entry->hash;
	while (*insertloc != NULL)
		insertloc = &((*insertloc)->cdr);
	*insertloc = entry;
}

void *aref_table_find(aref_table *h, void *key)
{
	unsigned hash = h->hashfunc(key);
	struct aref_tableentry *entry = h->table[(uint8_t)hash];
	while (entry != NULL && entry->hash != hash)
		entry = entry->cdr;
	return entry ? entry->data : NULL;
}

void *aref_table_delete(aref_table *h, void *key)
{
	unsigned hash = h->hashfunc(key);
	struct aref_tableentry **entry = h->table + (uint8_t)hash;

	while (*entry != NULL && (*entry)->hash != hash)
		entry = &((*entry)->cdr);
	if (*entry == NULL) return NULL;

	struct aref_tableentry *deleted = *entry;
	*entry = deleted->cdr;
	return deleted;
}

unsigned aref_djb2a(const void *data, size_t size)
{
	const unsigned char *str = data;
	const unsigned char *end = data + size;
	unsigned hash = 5381;

	for (const unsigned char *i = str; i != end; ++i)
		hash = ((hash << 5) + hash) ^ *i; /* (hash * 32) ^ *i */

	return hash;
}

inline unsigned aref_hash_string(const void *p)
{
	const char *mapname = p;
	return aref_djb2a(mapname, strlen(mapname));
}

unsigned aref_cihash_string(const void *data)
{
	const unsigned char *str = data;
	unsigned hash = 5381;

	for (const unsigned char *i = str; *i; ++i) {
		unsigned lower = tolower(*i);
		hash = ((hash << 5) + hash) ^ lower; /* (hash * 32) ^ lower */
	}

	return hash;
}
