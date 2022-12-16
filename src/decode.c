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

#include <decode.h>

#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>

#include <csv.h>
#include <mappool.h>

aref_fielddef mappool_fields[] = {
	{offsetof(aref_mapdata, code), AREF_FIELD_STR, 7},
	{offsetof(aref_mapdata, beatmapid), AREF_FIELD_INT64, sizeof(int64_t)},
	{offsetof(aref_mapdata, mode), AREF_FIELD_UINT8, sizeof(int8_t)},
	AREF_FIELDDEF_END
};

int aref_loadmappool(sqlite3 *db, FILE *f)
{
	int rowcount = 0;
	sqlite3_exec(db, "BEGIN TRANSACTION;", NULL, NULL, NULL);
	// clean start
	sqlite3_exec(db, "DELETE FROM mappool;", NULL, NULL, NULL);
	// not using aref_mappool_insert() as it
	// recompiles our query again and again
	sqlite3_stmt *load_query;
	sqlite3_prepare_v2(db, aref_mappool_insert_query, -1, &load_query, NULL);
	if (load_query == NULL) return 0;

	aref_mapdata map;

	while (AREF_CSV_NOTDONE(aref_readcsvline(f, &map, mappool_fields))) {
		sqlite3_bind_text(load_query, 1, map.code, -1, SQLITE_STATIC);
		sqlite3_bind_int64(load_query, 2, map.mode);
		sqlite3_bind_int(load_query, 3, map.beatmapid);
		sqlite3_step(load_query);
		rowcount += 1;
		sqlite3_reset(load_query);
	}

	sqlite3_finalize(load_query);
	sqlite3_exec(db, "COMMIT TRANSACTION;", NULL, NULL, NULL);
	return rowcount;
}

