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

#ifndef _AREF__MIGRATIONS_H
#define _AREF__MIGRATIONS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <sqlite3.h>

typedef struct aref_migration {
	int (*up)(sqlite3 *db);
	int (*down)(sqlite3 *db);
} aref_migration;

extern const aref_migration aref_dbmigration_initial_migration;
extern const aref_migration aref_dbmigration_add_players;

extern const aref_migration *aref_migrations[];

extern int aref_db_init(sqlite3 *db);

#ifdef __cplusplus
}
#endif

#endif /* !_AREF__MIGRATIONS_H */
