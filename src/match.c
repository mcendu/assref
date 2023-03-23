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

#include <match.h>

#include <string.h>

int aref_player_in_match(aref_match *match, aref_player *player)
{
	int in_red = strcmp(player->name, match->red);
	int in_blue = strcmp(player->name, match->blue);

	if (in_red == 0) return 1;
	if (in_blue == 0) return -1;
	return 0;
}

int aref_aggregate_score(int *rindivid, int rsize, int *bindivid, int bsize)
{
	int rtotal = 0, btotal = 0;
	for (int i = 0; i < rsize; ++i)
		rtotal += rindivid[i];
	for (int i = 0; i < bsize; ++i)
		btotal += bindivid[i];
	return rtotal - btotal;
}
