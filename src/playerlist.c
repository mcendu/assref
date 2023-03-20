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

#include <playerlist.h>

#include <sqlite3.h>
#include <stdlib.h>
#include <string.h>

static const char insert_query[]
	= u8"REPLACE INTO players (username,id,team) VALUES(:name,:id,:team)";
const char *aref_playerlist_insert_query = insert_query;

int aref_playerlist_insert(sqlite3 *db, aref_player *p)
{
	sqlite3_stmt *query;
	int status = sqlite3_prepare_v2(db, insert_query, sizeof(insert_query),
									&query, NULL);
	if (status != SQLITE_OK)
		return status; // failure

	sqlite3_bind_text(query, 1, p->name, -1, SQLITE_STATIC);
	sqlite3_bind_int64(query, 2, p->serverid);
	sqlite3_bind_text(query, 3, p->team, -1, SQLITE_STATIC);

	while ((status = sqlite3_step(query)) == SQLITE_ROW)
		;

	sqlite3_finalize(query);
	return !(status == SQLITE_DONE);
}

static const char find_query[]
	= u8"SELECT username,id,team FROM players WHERE username=?";
const char *aref_playerlist_find_query = find_query;

int aref_playerlist_find(sqlite3 *db, const char *name, aref_player *out)
{
	sqlite3_stmt *query;
	int status
		= sqlite3_prepare_v2(db, find_query, sizeof(find_query), &query, NULL);
	if (status != SQLITE_OK)
		return status;
	sqlite3_bind_text(query, 1, name, -1, SQLITE_STATIC);

	if ((status = sqlite3_step(query)) == SQLITE_ROW) {
		strncpy(out->name, (const char *)sqlite3_column_text(query, 0), 15);
		out->name[15] = 0;
		strncpy(out->team, (const char *)sqlite3_column_text(query, 2), 55);
		out->team[55] = 0;
		out->serverid = sqlite3_column_int64(query, 1);
	}

	sqlite3_finalize(query);
	return !(status == SQLITE_ROW);
}

static const char find_by_id_query[]
	= u8"SELECT username,id,team FROM players WHERE id=?";
const char *aref_playerlist_find_by_id_query = find_by_id_query;

int aref_playerlist_find_by_id(sqlite3 *db, uint64_t id, aref_player *out)
{
	sqlite3_stmt *query;
	int status = sqlite3_prepare_v2(db, find_by_id_query,
									sizeof(find_by_id_query), &query, NULL);
	if (status != SQLITE_OK)
		return status;
	sqlite3_bind_int64(query, 1, id);

	if ((status = sqlite3_step(query)) == SQLITE_ROW) {
		strncpy(out->name, (const char *)sqlite3_column_text(query, 0), 15);
		out->name[15] = 0;
		strncpy(out->team, (const char *)sqlite3_column_text(query, 2), 55);
		out->team[55] = 0;
		out->serverid = sqlite3_column_int64(query, 1);
	}

	sqlite3_finalize(query);
	return !(status == SQLITE_ROW);
}
