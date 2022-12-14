/* SPDX-License-Identifier: MIT
 * Copyright (C) 2022 McEndu et al.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice
 * (including the next paragraph) shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
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
 * @return If 0, indicates success; any other number indicates failure.
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
