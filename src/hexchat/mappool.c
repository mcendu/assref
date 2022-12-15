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

#include <decode.h>
#include <mappool.h>

void arefxchat_loadmappool(struct plugindata *data, char **word,
						   char **word_eol)
{
	if (word_eol[0][0] == 0) {
		hexchat_print(ph, "No mappool file specified");
		return;
	}

	FILE *f = fopen(word_eol[0], "r");
	int loaded = aref_loadmappool(data->db, f);
	fclose(f);

	hexchat_printf("Loaded %d maps from %s", loaded, word_eol[0]);
}

void arefxchat_setmap(struct plugindata *data, char **word, char **word_eol)
{
	if (word[0][0] == 0) {
		hexchat_print(ph, "No beatmap specified");
		return;
	}

	aref_mapdata map;
	if (aref_mappool_find(data->db, word[0], &data) != 0) {
		hexchat_printf(ph, "Cannot find beatmap \"%s\"", word[0]);
	} else {
		hexchat_commandf(ph, "SAY !mp map %d %d", map.beatmapid, map.mode);
		hexchat_printf(ph, "Set current map to %s", map.code);
	}
}