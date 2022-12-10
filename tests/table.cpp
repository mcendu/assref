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

#include <table.h>

#include <string.h>

#include <gtest/gtest.h>

unsigned hashstr(void *p)
{
	const char *str = (const char *)p;
	return aref_djb2a(str, strlen(str));
}

extern "C" struct data {
	const char *key;
	int number;
};

#define inittable(t) aref_inittable((t), hashstr);

class TestTable : public ::testing::Test
{
  protected:
	aref_table t;
	void SetUp() override
	{
		inittable(&t);
	}

	void TearDown() override
	{
		aref_freetable(&t);
	}
};

const char ALICE[] = "Alice";
const char BOB[] = "Bob";

const struct data dataset[] = {
	{ ALICE, 172 },
	{ BOB, 175 }
};

TEST_F(TestTable, basic)
{
	aref_table_insert(&t, (void *)ALICE, (void *)&(dataset[0]));
	aref_table_insert(&t, (void *)BOB, (void *)&(dataset[1]));

	struct data *alice = (data *)aref_table_find(&t, (void *)ALICE);
	EXPECT_STREQ(alice->key, ALICE);
	EXPECT_EQ(alice->number, 172);
}
