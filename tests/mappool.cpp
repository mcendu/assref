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

#include <mappool.h>

#include <gtest/gtest.h>

#include "dbtest.h"

class TestMappool : public TestDatabase
{
};

TEST_F(TestMappool, readwrite)
{
	aref_mapdata mapdata = {"rc1", 3, 3861836};
	aref_mapdata readmapdata;

	ASSERT_NE(db, nullptr);
	aref_mappool_insert(db, &mapdata);
	aref_mappool_find(db, "rc1", &readmapdata);

	EXPECT_STREQ(readmapdata.code, mapdata.code);
	EXPECT_EQ(readmapdata.beatmapid, mapdata.beatmapid);
	EXPECT_EQ(readmapdata.mode, mapdata.mode);
}

TEST_F(TestMappool, inject)
{
	aref_mapdata mapdata = {"'); --", 3, 3861836};
	aref_mapdata readmapdata = {"", 0, 0};

	ASSERT_NE(db, nullptr);
	aref_mappool_insert(db, &mapdata);
	aref_mappool_find(db, "'); --", &readmapdata);

	EXPECT_STREQ(readmapdata.code, mapdata.code);
}
