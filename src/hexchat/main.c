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

#include "os.h"

hexchat_plugin *ph = NULL;
static struct plugindata plugindata = {NULL};

const struct arefxchat_command command_list[] = {
	{"HELP",
	 "Usage: AREF HELP <command>, prints help text of an AssRef command",
	 arefxchat_help},
	{"LOAD", "Usage: AREF LOAD <path>, loads a database file", arefxchat_load},
	{"MAP", "Usage: AREF MAP <codename>, sets current beatmap",
	 arefxchat_setmap},
	{"MAPPOOL", "Usage: AREF MAPPOOL <path>, loads a mappool from CSV",
	 arefxchat_loadmappool},
	{NULL, NULL, NULL}};

void list_commands()
{
	hexchat_print(ph, "AREF subcommands:");
	for (const struct arefxchat_command *i = command_list; i->name != NULL;
		 ++i) {
		hexchat_printf(ph, "    %s", i->name);
	}
}

void find_help(char *command)
{
	for (const struct arefxchat_command *i = command_list; i->name != NULL;
		 ++i) {
		if (strcasecmp(i->name, command) == 0) {
			hexchat_print(ph, i->helptext);
			return;
		}
	}

	hexchat_printf(ph, "Not an AssRef command: %s", command);
	list_commands();
}

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
void arefxchat_help(struct plugindata *data, char **word, char **word_eol)
{
	if (word[0][0] == 0)
		list_commands();
	else
		find_help(word[0]);
}
#pragma GCC diagnostic pop

int run_ref_command(char **word, char **word_eol, void *userdata)
{
	struct plugindata *data = userdata;
	char *command_name = word[2];
	char **callback_word = &word[3];
	char **callback_wordeol = &word_eol[3];

	if (command_name[0] == 0) {
		hexchat_print(ph, "No AssRef subcommand specified");
		goto prompt_help;
	}

	for (const struct arefxchat_command *i = command_list; i->name != NULL;
		 ++i) {
		if (strcasecmp(i->name, command_name) == 0) {
			i->callback(data, callback_word, callback_wordeol);
			return HEXCHAT_EAT_PLUGIN;
		}
	}

	hexchat_printf(ph, "Not an AssRef command: %s", command_name);
prompt_help:
	hexchat_print(ph, "Use \"/aref help\" for a list of commands.");
	return HEXCHAT_EAT_PLUGIN;
}

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
