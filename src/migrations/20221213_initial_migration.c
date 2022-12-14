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

#include <migrations.h>
#include <stdlib.h>

static int up(sqlite3 *cursor)
{
	return sqlite3_exec(
		cursor,
		u8"BEGIN TRANSACTION;"

		u8"CREATE TABLE aref_metadata (key TEXT PRIMARY KEY, value);"

		u8"CREATE TABLE mappool ("
		u8"   mapcode CHAR(6) PRIMARY KEY,"
		u8"   mode INTEGER,"
		u8"   beatmapid INTEGER);"

		// set migration revision
		u8"REPLACE INTO aref_metadata (key, value) VALUES('revision', 0);"

		u8"COMMIT TRANSACTION;",
		NULL, NULL, NULL);
}

static int down(sqlite3 *cursor)
{
	return sqlite3_exec(cursor,
						u8"BEGIN TRANSACTION;"
						u8"DROP TABLE mappool;"
						u8"DROP TABLE aref_metadata;"
						u8"COMMIT TRANSACTION;",
						NULL, NULL, NULL);
}

const aref_migration aref_dbmigration_initial_migration = {up, down};
