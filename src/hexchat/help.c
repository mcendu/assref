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
