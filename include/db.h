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

#ifndef _AREF__DB_H
#define _AREF__DB_H

#ifdef __cplusplus
extern "C" {
#endif

#include <sqlite3.h>

/**
 * @brief Open or create a database for the tournament.
 *
 * @param filename The filename of the database to open or create.
 *      See <https://www.sqlite.org/c3ref/open.html> for more details.
 * @param cursor A handle to the database is returned here.
 * @return See <https://www.sqlite.org/rescode.html>.
 */
extern int aref_db_open(const char *filename, sqlite3 **cursor);

extern int aref_db_migrate(sqlite3 *cursor);

#ifdef __cplusplus
}
#endif

#endif /* !_AREF__DB_H */
