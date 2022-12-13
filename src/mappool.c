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

#include <sqlite3.h>
#include <stdlib.h>
#include <string.h>

#define ALLOCATION_UNIT 32

static const char insertion_query[]
	= u8"REPLACE INTO mappool (mapcode,mode,beatmapid) "
	  u8"VALUES(:code,:mode,:beatmapid);";
const char *aref_mappool_insert_query = insertion_query;

int aref_mappool_insert(sqlite3 *db, aref_mapdata *map)
{
	sqlite3_stmt *query;
	int status = sqlite3_prepare_v2(db, insertion_query, -1, &query, NULL);
	if (status != SQLITE_OK)
		return status; // failure

	sqlite3_bind_text(query, 1, map->code, 7, SQLITE_STATIC);
	sqlite3_bind_int64(query, 2, map->mode);
	sqlite3_bind_int(query, 3, map->beatmapid);

	while ((status = sqlite3_step(query)) == SQLITE_ROW)
		;

	sqlite3_finalize(query);
	return status == SQLITE_DONE ? 0 : status;
}

const char find_query[]
	= u8"SELECT mapcode,mode,beatmapid FROM mappool WHERE mapcode=?";
const char *aref_mappool_find_query = find_query;

int aref_mappool_find(sqlite3 *db, const char *code, aref_mapdata *data)
{
	sqlite3_stmt *query;
	int status = sqlite3_prepare_v2(db, find_query, -1, &query, NULL);
	if (status != SQLITE_OK)
		return status; // failure

	sqlite3_bind_text(query, 1, code, 7, SQLITE_STATIC);

	status = sqlite3_step(query);
	while (status == SQLITE_ROW) {
		strcpy(data->code, (const char *)sqlite3_column_text(query, 0));
		data->mode = sqlite3_column_int(query, 1);
		data->beatmapid = sqlite3_column_int64(query, 2);
	}

	sqlite3_finalize(query);
	return status == SQLITE_DONE ? 0 : status;
}
