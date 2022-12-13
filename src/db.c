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
					   checkdb, NULL);
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
						   -1, getrev, NULL);
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
