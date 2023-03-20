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

#include <strings.h>

const struct arefxchat_command command_list[] = {
	{"HELP",
	 "Usage: AREF HELP <command>, prints help text of an AssRef command",
	 arefxchat_help},
	{"LOAD", "Usage: AREF LOAD <path>, loads a database file", arefxchat_load},
	{"MAP", "Usage: AREF MAP <codename>, sets current beatmap",
	 arefxchat_setmap},
	{"MAPPOOL", "Usage: AREF MAPPOOL <path>, loads a mappool from CSV",
	 arefxchat_loadmappool},
	{"PLAYERLIST",
	 "Usage: AREF PLAYERLIST <path>, loads a player list from CSV",
	 arefxchat_loadplayerlist},
	{NULL, NULL, NULL}};

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
