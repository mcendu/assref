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

static int up(sqlite3 *db)
{
	return sqlite3_exec(
		db,
		u8"BEGIN TRANSACTION;"

		u8"CREATE TABLE players ("
		u8"   username CHAR(15) PRIMARY KEY,"
		u8"   id INTEGER,"
		u8"   team VARCHAR(63));"

		// set migration revision
		u8"UPDATE aref_metadata SET value=1 WHERE key='revision';"

		u8"COMMIT TRANSACTION;",
		NULL, NULL, NULL);
}

static int down(sqlite3 *db)
{
	return sqlite3_exec(
		db,
		u8"BEGIN TRANSACTION;"
		u8"DROP TABLE players;"
		u8"UPDATE aref_metadata SET value=0 WHERE key='revision');"
		u8"COMMIT TRANSACTION;",
		NULL, NULL, NULL);
}

const aref_migration aref_dbmigration_add_players = {up, down};
