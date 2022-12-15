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

#include <mappool.h>

#include <sqlite3.h>
#include <stdlib.h>
#include <string.h>

static const char insertion_query[]
	= u8"REPLACE INTO mappool (mapcode,mode,beatmapid) "
	  u8"VALUES(lower(:code),:mode,:beatmapid);";
const char *aref_mappool_insert_query = insertion_query;

int aref_mappool_insert(sqlite3 *db, aref_mapdata *map)
{
	sqlite3_stmt *query;
	int status = sqlite3_prepare_v2(db, insertion_query, -1, &query, NULL);
	if (status != SQLITE_OK)
		return status; // failure

	sqlite3_bind_text(query, 1, map->code, -1, SQLITE_STATIC);
	sqlite3_bind_int64(query, 2, map->mode);
	sqlite3_bind_int(query, 3, map->beatmapid);

	while ((status = sqlite3_step(query)) == SQLITE_ROW)
		;

	sqlite3_finalize(query);
	return status == SQLITE_DONE ? 0 : status;
}

static const char find_query[]
	= u8"SELECT mapcode,mode,beatmapid FROM mappool WHERE mapcode=lower(?)";
const char *aref_mappool_find_query = find_query;

int aref_mappool_find(sqlite3 *db, const char *code, aref_mapdata *data)
{
	sqlite3_stmt *query;
	int status = sqlite3_prepare_v2(db, find_query, -1, &query, NULL);
	if (status != SQLITE_OK)
		return status; // failure

	sqlite3_bind_text(query, 1, code, -1, SQLITE_STATIC);

	status = sqlite3_step(query);
	if (status == SQLITE_ROW) {
		strcpy(data->code, (const char *)sqlite3_column_text(query, 0));
		data->mode = sqlite3_column_int(query, 1);
		data->beatmapid = sqlite3_column_int64(query, 2);
	}

	sqlite3_finalize(query);
	return !(status == SQLITE_ROW);
}
