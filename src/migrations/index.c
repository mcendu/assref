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

#include <migrations.h>
#include <stdlib.h>

const char current_schema[]
	= (u8"BEGIN TRANSACTION;"

	   u8"CREATE TABLE aref_metadata (key TEXT PRIMARY KEY, value);"

	   u8"CREATE TABLE mappool ("
	   u8"mapcode CHAR(6) PRIMARY KEY,"
	   u8"mode INTEGER,"
	   u8"beatmapid INTEGER);"

	   // set migration revision
	   u8"REPLACE INTO aref_metadata (key, value) VALUES('revision', 0);"

	   u8"COMMIT TRANSACTION;");

const aref_migration *aref_migrations[] = {
	&aref_dbmigration_initial_migration,
	NULL /* allows easy checking if a migration is latest */
};

int aref_db_init(sqlite3 *db)
{
	return sqlite3_exec(db, current_schema, NULL, NULL, NULL);
}
