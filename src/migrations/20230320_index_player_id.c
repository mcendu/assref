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
	return sqlite3_exec(db, u8"CREATE INDEX players_id_index ON players (id);",
						NULL, NULL, NULL);
}

static int down(sqlite3 *db)
{
	return sqlite3_exec(db, u8"DROP INDEX players_id_index;", NULL, NULL, NULL);
}

const aref_migration aref_dbmigration_index_player_id = {up, down};
