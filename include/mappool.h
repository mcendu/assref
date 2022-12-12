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
#include <table.h>

typedef struct {
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

typedef struct {
	aref_mapdata *pool;
	size_t size;
	size_t capacity;
	aref_table table;
} aref_mappool;

extern void aref_initmappool(aref_mappool *mappool);
extern void aref_freemappool(aref_mappool *mappool);

extern aref_mapdata *aref_mappool_addemptyentry(aref_mappool *mappool);

#define aref_mappool_insert(mappool, data) \
	aref_table_insert(&(mappool)->table, (void *)data->code, (void *)data)
#define aref_mappool_find(mappool, code) \
	(aref_mapdata *)aref_table_find(&(mappool)->table, (void *)(code))

#ifdef __cplusplus
}
#endif

#endif /* !_AREF__MAPPOOL_H */
