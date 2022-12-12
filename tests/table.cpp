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

extern "C" struct data {
	const char *key;
	int number;
};

#define inittable(t) aref_inittable((t), aref_hash_string);

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

const struct data dataset[]
	= {{(const char *)"Alice", 172}, {(const char *)"Bob", 175}};

using DeathTestTable = TestTable;

TEST_F(TestTable, basic)
{
	// note that C++ is stricter about pointers than C, hence the
	// load of pointer conversions
	aref_table_insert(&t, (void *)"Alice", (void *)&(dataset[0]));
	aref_table_insert(&t, (void *)"Bob", (void *)&(dataset[1]));

	struct data *alice = (data *)aref_table_find(&t, (void *)"Alice");
	EXPECT_STREQ(alice->key, "Alice");
	EXPECT_EQ(alice->number, 172);

	EXPECT_EQ(aref_table_find(&t, (void *)"Carol"), nullptr);
}

extern "C" struct int_indexed_data {
	uint32_t key;
	uint32_t data;
};

unsigned hash_int(const void *x)
{
	return aref_djb2a(x, sizeof(int));
}

// https://arxiv.org/abs/2001.05304
#define lcg64(x) (0xd1342543de82ef95 * (x) + 1)

TEST_F(TestTable, largedata)
{
	uint64_t lcg_state = 128;
	int_indexed_data *data = new int_indexed_data[500];

	t.hashfunc = hash_int;
	for (int i = 0; i < 500; ++i) {
		uint32_t key = i;
		lcg_state = lcg64(lcg_state);
		uint32_t value = lcg_state >> 32;
		data[i] = (int_indexed_data){key, value};
		aref_table_insert(&t, &key, &data[i]);
	}

	int lookup = 499;
	ASSERT_NE(aref_table_find(&t, &lookup), nullptr);

	delete []data;
}

TEST_F(TestTable, free)
{
	aref_freetable(&t);
	EXPECT_EQ(t.pool, nullptr);
}

TEST_F(TestTable, cihash)
{
	EXPECT_EQ(aref_cihash_string("Hello world"),
			  aref_cihash_string("hELLO WORLD"));
}
