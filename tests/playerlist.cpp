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

#include <playerlist.h>

#include "dbtest.h"
#include <gtest/gtest.h>

class TestPlayer : TestDatabase
{
};

TEST_F(TestDatabase, readwrite)
{
	aref_player player = {"foo", 1, "bar"};
	aref_player readdata;

	ASSERT_NE(db, nullptr);
	aref_playerlist_insert(db, &player);

	readdata = {"", 0, ""};
	aref_playerlist_find(db, "foo", &readdata);
	ASSERT_EQ(readdata.serverid, 1);
	ASSERT_STREQ(readdata.name, "foo");

	readdata = {"", 0, ""};
	aref_playerlist_find_by_id(db, 1, &readdata);
	ASSERT_EQ(readdata.serverid, 1);
	ASSERT_STREQ(readdata.name, "foo");
}
