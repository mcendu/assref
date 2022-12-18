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

#include <sqlite3.h>
#include <stdio.h>
#include <stdlib.h>

#include <csv.h>
#include <mappool.h>
#include <playerlist.h>

const aref_fielddef mappool_fields[]
	= {{offsetof(aref_mapdata, code), AREF_FIELD_STR, 7},
	   {offsetof(aref_mapdata, beatmapid), AREF_FIELD_UINT64, 0},
	   {offsetof(aref_mapdata, mode), AREF_FIELD_UINT8, 0},
	   AREF_FIELDDEF_END};

int aref_loadmappool(sqlite3 *db, FILE *f)
{
	int rowcount = 0;
	sqlite3_exec(db, "BEGIN TRANSACTION;", NULL, NULL, NULL);
	// clean start
	sqlite3_exec(db, "DELETE FROM mappool;", NULL, NULL, NULL);

	int result;
	aref_mapdata map;
	// not using aref_mappool_insert() as it
	// recompiles our query again and again
	sqlite3_stmt *load_query;
	sqlite3_prepare_v2(db, aref_mappool_insert_query, -1, &load_query, NULL);
	if (load_query == NULL)
		return 0;
	while (
		AREF_CSV_NOTDONE(result = aref_readcsvline(f, &map, mappool_fields))) {
		if (result == AREF_CSV_MALFORMED)
			continue;
		sqlite3_bind_text(load_query, 1, map.code, -1, SQLITE_STATIC);
		sqlite3_bind_int64(load_query, 2, map.mode);
		sqlite3_bind_int(load_query, 3, map.beatmapid);
		if (sqlite3_step(load_query) == SQLITE_DONE)
			rowcount += 1;
		sqlite3_reset(load_query);
	}
	sqlite3_finalize(load_query);

	sqlite3_exec(db, "COMMIT TRANSACTION;", NULL, NULL, NULL);
	return rowcount;
}

const aref_fielddef players_fields[]
	= {{offsetof(aref_player, name), AREF_FIELD_STR, 16},
	   {offsetof(aref_player, serverid), AREF_FIELD_UINT64, 0},
	   {offsetof(aref_player, team), AREF_FIELD_STR, 56},
	   AREF_FIELDDEF_END};

int aref_loadplayerlist(sqlite3 *db, FILE *f)
{
	int rowcount = 0;
	sqlite3_exec(db, "BEGIN TRANSACTION;", NULL, NULL, NULL);
	// clean start
	sqlite3_exec(db, "DELETE FROM players;", NULL, NULL, NULL);

	int result;
	aref_player entry;
	sqlite3_stmt *query;
	sqlite3_prepare_v2(db, aref_playerlist_insert_query, -1, &query, NULL);
	if (query == NULL)
		return 0;
	while (AREF_CSV_NOTDONE(result
							= aref_readcsvline(f, &entry, players_fields))) {
		if (result == AREF_CSV_MALFORMED)
			continue;
		sqlite3_bind_text(query, 1, entry.name, -1, SQLITE_STATIC);
		sqlite3_bind_int64(query, 2, entry.serverid);
		sqlite3_bind_text(query, 3, entry.team, -1, SQLITE_STATIC);
		if (sqlite3_step(query) == SQLITE_DONE)
			rowcount += 1;
		sqlite3_reset(query);
	}

	sqlite3_exec(db, "COMMIT TRANSACTION;", NULL, NULL, NULL);
	return rowcount;
}
