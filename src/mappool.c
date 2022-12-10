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

#include <mappool.h>

#include <stdlib.h>
#include <string.h>

#define ALLOCATION_UNIT 32

unsigned hash_mapname(void *p)
{
	char *mapname = p;
	return aref_djb2a(mapname, strlen(mapname));
}

void aref_initmappool(aref_mappool *mappool)
{
	mappool->pool = malloc(ALLOCATION_UNIT * sizeof(aref_mapdata));
	mappool->size = 0;
	mappool->capacity = ALLOCATION_UNIT;
	aref_inittable(&mappool->table, hash_mapname);
}

void aref_freemappool(aref_mappool *mappool)
{
	free(mappool->pool);
	mappool->pool = NULL;
}

aref_mapdata *aref_mappool_addemptyentry(aref_mappool *mappool)
{
	mappool->size += 1;
	if (mappool->size > mappool->capacity) {
		mappool->capacity += ALLOCATION_UNIT;
		mappool->pool = realloc(mappool->pool, mappool->capacity * sizeof(aref_mapdata));
	}

	return mappool->pool + mappool->size - 1;
}
