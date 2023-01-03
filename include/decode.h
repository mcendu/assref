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

#ifndef _AREF__DECODE_H
#define _AREF__DECODE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <mappool.h>
#include <sqlite3.h>
#include <stdio.h>

/**
 * @brief Load a mappool from CSV into the database.
 * @param file The file to read data from.
 * @return The number of entries read.
 */
extern int aref_loadmappool(sqlite3 *, FILE *file);

/**
 * @brief Load a player list from CSV into the database.
 * @param file The file to read data from.
 * @return The number of entries read.
 */
extern int aref_loadplayerlist(sqlite3 *, FILE *file);

#ifdef __cplusplus
}
#endif

#endif /* !_AREF__DECODE_H */
