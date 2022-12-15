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
#include "commands.h"

#include <stdlib.h>
#include <string.h>

hexchat_plugin *ph = NULL;
static struct plugindata plugindata = {};

const struct arefxchat_command command_list[]
	= {{"HELP",
		"Usage: AREF HELP <command>, prints help text of an AssRef command",
		arefxchat_help},
		{"LOAD", "Usage: AREF LOAD <path>, loads a database file", arefxchat_load},
	   {NULL, NULL, NULL}};

void arefxchat_help(struct plugindata *data, char **word, char **word_eol)
{
	hexchat_print(ph, "AREF subcommands:");
	for (const struct arefxchat_command *i = command_list; i->name != NULL;
		 ++i) {
		hexchat_printf(ph, "    %s", i->name);
	}
}

int run_ref_command(char **word, char **word_eol, void *userdata)
{
	struct plugindata *data = userdata;
	char *command_name = word[2];
	char **callback_word = &word[3];
	char **callback_wordeol = &word_eol[3];

	for (const struct arefxchat_command *i = command_list; i->name != NULL;
		 ++i) {
		if (strcasecmp(i->name, command_name) == 0) {
			i->callback(data, callback_word, callback_wordeol);
			return HEXCHAT_EAT_PLUGIN;
		}
	}

	hexchat_printf(ph, "Not an AssRef command: %s", command_name);
	hexchat_print(ph, "Use \"/aref help\" for a list of commands.");
	return HEXCHAT_EAT_PLUGIN;
}

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
