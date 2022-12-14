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

#include <gtest/gtest.h>

#include <db.h>
#include <sqlite3.h>

#include "dbtest.h"

sqlite3 *TestDatabase::db = 0;

void TestDatabase::SetUpTestSuite()
{
	aref_db_open((char *)"test.db", &db);
}

void TestDatabase::TearDownTestSuite()
{
	sqlite3_close(db);
	unlink("test.db");
}

testing::AssertionResult DbAccessSuccess(int code, char *error)
{
	if (code != SQLITE_OK && code != SQLITE_ROW && code != SQLITE_DONE)
		return testing::AssertionFailure()
			   << "Database operation failed: " << error;
	return testing::AssertionSuccess();
}
