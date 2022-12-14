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
#include "dbtest.h"

class TestDecode : public TestDatabase
{

};

TEST_F(TestDecode, poolentry)
{
	aref_mapdata mapdata;
	FILE *f = fopen("tests/data/poolentry.csv", "r");

	aref_decodepoolentry(&mapdata, f);
	ASSERT_STREQ(mapdata.code, "rc1");
	ASSERT_EQ(mapdata.beatmapid, 3861836);
	ASSERT_EQ(mapdata.mode, 3);
	aref_decodepoolentry(&mapdata, f);
	ASSERT_STREQ(mapdata.code, "rc2");
	ASSERT_EQ(mapdata.beatmapid, 3573500);
	aref_decodepoolentry(&mapdata, f);
	ASSERT_STREQ(mapdata.code, "rc3");
	aref_decodepoolentry(&mapdata, f);
	ASSERT_STREQ(mapdata.code, "rc4");
}

TEST_F(TestDecode, pool)
{
	ASSERT_NE(db, nullptr);
	aref_mapdata data;

	FILE *f = fopen("tests/data/pool.csv", "r");
	EXPECT_EQ(aref_loadmappool(db, f), 11);
	fclose(f);

	aref_mappool_find(db, "rc4", &data);
	EXPECT_STREQ(data.code, "rc4");
	EXPECT_EQ(data.beatmapid, 2717089);
}
