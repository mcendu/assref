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

#include <match.h>

#include <gtest/gtest.h>

TEST(TestMatch, playerInMatch)
{
	aref_match m = {"a", "b", 0, 0};
	aref_player a = {"a", 1, "a"};
	aref_player b = {"b", 2, "b"};
	aref_player c = {"c", 3, "c"};

	ASSERT_EQ(aref_player_in_match(&m, &a), 1);
	ASSERT_EQ(aref_player_in_match(&m, &b), -1);
	ASSERT_EQ(aref_player_in_match(&m, &c), 0);
}
