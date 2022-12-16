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

#include "plugindata.h"

#include <string.h>
#include <db.h>

int load_database(struct plugindata *data, char *path)
{
	// close database to prevent memory leak
	sqlite3_close(data->db);
	int result = aref_db_open(path, &data->db);

	if (result != SQLITE_OK) {
		hexchat_printf(ph, "Cannot open database %s: %s",
			path, sqlite3_errmsg(data->db));
	}

	return result;
}

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
void arefxchat_load(struct plugindata *data, char **word, char **word_eol)
{
	char path[512];
	strncpy(path, word_eol[0], 512);
	path[511] = 0;

	hexchat_pluginpref_set_str(ph, "database", path);
	if (load_database(data, path) == SQLITE_OK) {
		hexchat_print(ph, "Successfully opened database.");
	}
}
#pragma GCC diagnostic pop

int init_database(struct plugindata *data)
{
	// From XChat and HexChat devs (Why should I read the src for this?):
	// > All users of this must ensure dest is >= 512...
	char path[512];
	if (!hexchat_pluginpref_get_str(ph, "database", path)) {
		WARNING("Database not configured.");
		WARNING("");
		WARNING("AssRef would connect to an in-memory database.");
		WARNING("All data would be lost when HexChat is closed.");
		WARNING("To load a database on disk, use \"/AREF LOAD\".");
		strncpy(path, ":memory:", 256);
	}

	return load_database(data, path);
}
