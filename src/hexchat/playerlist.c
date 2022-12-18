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

#include <errno.h>
#include <string.h>

#include <decode.h>
#include <playerlist.h>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

void arefxchat_loadplayerlist(struct plugindata *data, char **word,
							  char **word_eol)
{
	if (word_eol[0][0] == 0) {
		hexchat_print(ph, "No player list specified");
		return;
	}

	FILE *f = fopen(word_eol[0], "r");
	if (f == NULL) {
		hexchat_printf(ph, "Cannot open player list %s: %s", word_eol[0],
					   strerror(errno));
		return;
	}

	int loaded = aref_loadplayerlist(data->db, f);
	fclose(f);

	hexchat_printf(ph, "Loaded %d player entries from %s", loaded, word_eol[0]);
}

#pragma GCC diagnostic pop
