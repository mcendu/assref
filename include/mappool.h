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

#ifndef _AREF__MAPPOOL_H
#define _AREF__MAPPOOL_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <sqlite3.h>

typedef struct aref_mapdata {
	/**
	 * @brief A codename used to identify the beatmap.
	 */
	char code[7];
	/**
	 * @brief The gamemode (e.g. osu!) of the beatmap.
	 */
	uint8_t mode;
	/**
	 * @brief The BeatmapID used to query BanchoBot.
	 */
	uint64_t beatmapid;
} aref_mapdata;

enum aref_mode {
	AREF_MODE_STD,
	AREF_MODE_TAIKO,
	AREF_MODE_CATCH,
	AREF_MODE_MANIA
};

/*
 * Methods
 */

/**
 * @brief Add a new beatmap to the mappool.
 *
 * @param data The beatmap to insert.
 * @return If 0, indicates success; any other number indicates failure.
 */
extern int aref_mappool_insert(sqlite3 *, aref_mapdata *data);
/**
 * @brief Look up a beatmap by its code name.
 *
 * @param code The code name of a beatmap.
 * @param data A pointer to which beatmap data found is written.
 * @return If 0, indicates that a map has been found.
 */
extern int aref_mappool_find(sqlite3 *, const char *code, aref_mapdata *data);

/*
 * Database queries
 */
/**
 * @brief Add a new beatmap to the mappool.
 * @param 1 The code name of the beatmap.
 * @param 2 The game mode of the beatmap.
 * @param 3 The identifier of the beatmap on osu! servers.
 */
extern const char *aref_mappool_insert_query;
extern const char *aref_mappool_find_query;

#ifdef __cplusplus
}
#endif

#endif /* !_AREF__MAPPOOL_H */
