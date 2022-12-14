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

#include <db.h>

#include <migrations.h>
#include <stdlib.h>

int aref_db_open(char *filename, sqlite3 **cursor)
{
	int status = sqlite3_open_v2(
		filename, cursor, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, NULL);
	if (status != SQLITE_OK)
		return status;

	return aref_db_migrate(*cursor);
}

int aref_db_migrate(sqlite3 *cursor)
{
	int hasdata = 0;
	int dbrev;

	// check existence of data
	sqlite3_stmt *checkdb;
	sqlite3_prepare_v2(cursor, u8"SELECT name FROM sqlite_master;", -1,
					   &checkdb, NULL);
	if (sqlite3_step(checkdb) == SQLITE_ROW) { // exists
		hasdata = 1;
	}
	sqlite3_finalize(checkdb);

	if (hasdata) {
		sqlite3_stmt *getrev;
		int resultcode;
		sqlite3_prepare_v2(cursor,
						   u8"SELECT value FROM aref_metadata"
						   u8" WHERE key='revision'",
						   -1, &getrev, NULL);
		if ((resultcode = sqlite3_step(getrev)) == SQLITE_ROW) {
			dbrev = sqlite3_column_int(getrev, 0);

			for (int i = dbrev + 1; aref_migrations[i] != NULL; ++i) {
				int result = aref_migrations[i]->up(cursor);
				if (result != SQLITE_OK) return result;
			}
			return SQLITE_OK;
		} else {
			// likely not our database, leave it here
			sqlite3_finalize(getrev);
			return resultcode;
		}
	} else {
		return aref_db_init(cursor);
	}
}
