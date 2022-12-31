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

#include <stdio.h>
#include <textio.h>

#include <gtest/gtest.h>

const char refstring[]
	= "This line has the rightful Unix line endings.\n"
	  "This line ends the DOS way.\n"
	  "This is a line ending in the long gone ways of classic Mac.\n"
	  "This is just another line.\n";

TEST(TestSomething, lineconv)
{
	int c;
	FILE *f = fopen("tests/data/getc.txt", "rb");
	for (auto i = refstring; (c = aref_getc(f)) != EOF; ++i) {
		ASSERT_EQ(c, *i);
	}
}
