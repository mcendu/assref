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

#include "commands.h"
#include "plugindata.h"

#include <stdlib.h>
#include <string.h>
#include <strings.h>

hexchat_plugin *ph = NULL;
static struct plugindata plugindata = {NULL};

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
int hexchat_plugin_init(hexchat_plugin *xchat, char **plugin_name,
						char **plugin_desc, char **plugin_version, char *arg)
{
	ph = xchat;

	*plugin_name = "assref";
	*plugin_desc = "osu! tournament referee's robotic assistant";
	*plugin_version = "0.1";

	init_database(&plugindata);

	hexchat_hook_command(ph, "aref", HEXCHAT_PRI_NORM, run_ref_command,
						 "Usage: AREF <subcommand> ...", &plugindata);

	hexchat_print(ph, "AssRef loaded.");
	return 1;
}

int hexchat_plugin_deinit(hexchat_plugin *xchat)
{
	sqlite3_close(plugindata.db);
	hexchat_print(ph, "AssRef unloaded.");
	return 1;
}
#pragma GCC diagnostic pop
