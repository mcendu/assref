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

#include <decode.h>

#include <mappool.h>

#include <gtest/gtest.h>

TEST(TestDecode, mappool)
{
	aref_mapdata mapdata;
	FILE *f = fopen("tests/data/pool.csv", "r");

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
