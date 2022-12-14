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

#include <decode.h>

#include <gtest/gtest.h>

#include <mappool.h>
#include <playerlist.h>
#include "dbtest.h"

class TestDecode : public TestDatabase
{

};

TEST_F(TestDecode, pool)
{
	ASSERT_NE(db, nullptr);
	aref_mapdata data;

	FILE *f = fopen("tests/data/pool.csv", "r");
	ASSERT_NE(f, nullptr);
	EXPECT_EQ(aref_loadmappool(db, f), 11);
	fclose(f);

	aref_mappool_find(db, "rc4", &data);
	EXPECT_STREQ(data.code, "rc4");
	EXPECT_EQ(data.beatmapid, 2717089);

	sqlite3_exec(db, "DELETE FROM mappool;", 0, 0, 0);
}

TEST_F(TestDecode, players)
{
	ASSERT_NE(db, nullptr);

	FILE *f = fopen("tests/data/players.csv", "r");
	ASSERT_NE(f, nullptr);
	EXPECT_EQ(aref_loadplayerlist(db, f), 7);
	fclose(f);

	sqlite3_exec(db, "DELETE FROM players;", 0, 0, 0);
}
