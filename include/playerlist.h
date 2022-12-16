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

#ifndef _AREF__PLAYERLIST_H
#define _AREF__PLAYERLIST_H

#ifdef __cplusplus
extern "C" {
#endif

#include <sqlite3.h>
#include <stdint.h>

typedef struct {
	/**
	 * @brief The name of the player.
	 */
	char name[16];
	/**
	 * @brief The number of the player on osu! servers.
	 */
	uint64_t serverid;
	/**
	 * @brief The name of the team.
	 */
	char team[56];
} aref_player;

extern const char *aref_playerlist_insertion_query;
extern const char *aref_playerlist_find_query;

extern int aref_playerlist_insert(sqlite3 *, aref_player *playerdata);
extern int aref_playerlist_find(sqlite3 *, const char *playername,
								aref_player *out);

#ifdef __cplusplus
}
#endif

#endif /* !_AREF__PLAYERLIST_H */
