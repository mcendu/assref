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

#ifndef _AREFXCHAT__PLUGINDATA_H
#define _AREFXCHAT__PLUGINDATA_H

#include <hexchat-plugin.h>
#include <sqlite3.h>

/* required to be a global variable as otherwise it won't build on win32 */
extern hexchat_plugin *ph;

struct plugindata {
	sqlite3 *db;
};

#define WARNING(str) \
	hexchat_emit_print(ph, "Private Message", "AssRef", (str), NULL)

#endif /* !_AREFXCHAT__PLUGINDATA_H */
