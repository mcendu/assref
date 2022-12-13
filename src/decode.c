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

#include <decode.h>

#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>

#include <csv.h>
#include <mappool.h>

void aref_loadmappool(sqlite3 *db, FILE *f)
{
	// not using aref_mappool_insert() as it
	// recompiles our query again and again
	sqlite3_stmt *load_query;
	sqlite3_prepare_v2(db, aref_mappool_insert_query, -1, &load_query, NULL);
	if (load_query == NULL) return;

	aref_mapdata map;

	while (!feof(f)) {
		aref_decodepoolentry(&map, f);

		sqlite3_bind_text(load_query, 1, map.code, -1, SQLITE_STATIC);
		sqlite3_bind_int64(load_query, 2, map.mode);
		sqlite3_bind_int(load_query, 3, map.beatmapid);
		sqlite3_step(load_query);
		sqlite3_reset(load_query);
	}

	sqlite3_finalize(load_query);
}

void aref_decodepoolentry(aref_mapdata *entry, FILE *f)
{
	char buf[24];
	char end;

	int c = getc(f);

	if (c == EOF) // ending with a newline
		return;
	else
		ungetc(c, f);

	// Code,BeatmapID,Mode
	aref_readfield(entry->code, f, 7, &end);
	if (end == EOF || end == '\n')
		return;

	aref_readfield(buf, f, 24, &end);
	entry->beatmapid = strtoull(buf, NULL, 0);
	if (end == EOF || end == '\n')
		return;

	aref_readfield(buf, f, 24, &end);
	entry->mode = (uint8_t)strtol(buf, NULL, 0);
	if (end == EOF || end == '\n')
		return;

	aref_fskipline(f);
}
