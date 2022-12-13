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

#include <gtest/gtest.h>

#include <db.h>
#include <sqlite3.h>

static sqlite3 *db;

class TestDatabase : public ::testing::Test
{
  public:
	static void SetUpTestSuite()
	{
		aref_db_open((char *)":memory:", &db);
	}

	static void TearDownTestSuite()
	{
		sqlite3_close(db);
	}
};

testing::AssertionResult AccessSuccess(int code, char *error)
{
	if (code != SQLITE_OK && code != SQLITE_ROW && code != SQLITE_DONE)
		return testing::AssertionFailure()
			   << "Database operation failed: " << error;
	return testing::AssertionSuccess();
}

TEST_F(TestDatabase, write)
{
	ASSERT_NE(db, nullptr);
	char *error;
	int result = sqlite3_exec(
		db, u8"INSERT OR ABORT INTO mappool VALUES('rc1', 3861836, 3)", 0, 0,
		&error);
	EXPECT_TRUE(AccessSuccess(result, error));
	sqlite3_free(error);
}
