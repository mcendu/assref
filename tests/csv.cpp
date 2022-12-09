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

#include <csv.h>

#include <cstdio>
#include <cstdlib>

#include <gtest/gtest.h>

TEST(TestCsv, basic)
{
	char str[8];
	FILE *f = fopen("tests/data/basic.csv", "r");
	ASSERT_NE(f, nullptr);

	EXPECT_EQ(aref_readfield(str, f, 8, NULL), 5);
	EXPECT_STREQ(str, "test1");
	EXPECT_EQ(aref_readfield(str, f, 8, NULL), 5);
	EXPECT_STREQ(str, "test2");
	EXPECT_EQ(aref_readfield(str, f, 8, NULL), 5);
	EXPECT_STREQ(str, "test3");
	EXPECT_EQ(aref_readfield(str, f, 8, NULL), 0);
	EXPECT_STREQ(str, "");
	fclose(f);
}

TEST(TestCsv, multiline)
{
	char str[8];
	char end;
	FILE *f = fopen("tests/data/multiline.csv", "r");
	ASSERT_NE(f, nullptr);

	aref_readfield(str, f, 8, &end);
	EXPECT_EQ(end, ',');
	aref_readfield(str, f, 8, &end);
	EXPECT_EQ(end, '\n');
	aref_readfield(str, f, 8, &end);
	EXPECT_STREQ(str, "Bob");
	EXPECT_EQ(end, ',');

	fclose(f);
}

const char multiline_str[] = "Alice,172\n"
							 "Bob,175\n";

TEST(TestCsv, string)
{
	char astr[8];
	char bstr[8];
	char aend, bend;
	const char *ptr = multiline_str;

	FILE *f = fopen("tests/data/multiline.csv", "r");
	ASSERT_NE(f, nullptr);

	// "Alice"
	aref_readfield(astr, f, 8, &aend);
	ptr += aref_sreadfield(bstr, ptr, 8, &bend) + 1;
	EXPECT_STREQ(astr, bstr);
	EXPECT_EQ(aend, bend);
	// "172"
	aref_readfield(astr, f, 8, &aend);
	ptr += aref_sreadfield(bstr, ptr, 8, &bend) + 1;
	EXPECT_STREQ(astr, bstr);
	EXPECT_EQ(aend, bend);
	// "Bob"
	aref_readfield(astr, f, 8, &aend);
	ptr += aref_sreadfield(bstr, ptr, 8, &bend) + 1;
	EXPECT_STREQ(astr, bstr);
	EXPECT_EQ(aend, bend);
	// "175"
	aref_readfield(astr, f, 8, &aend);
	ptr += aref_sreadfield(bstr, ptr, 8, &bend) + 1;
	EXPECT_STREQ(astr, bstr);
	EXPECT_EQ(aend, bend);
	// EOF
	aref_readfield(astr, f, 8, &aend);
	ptr += aref_sreadfield(bstr, ptr, 8, &bend) + 1;
	EXPECT_EQ(aend, EOF);
	EXPECT_EQ(bend, 0);

	fclose(f);
}

TEST(TestCsv, empty)
{
	char str[8];
	FILE *f = fopen("tests/data/empty.csv", "r");
	ASSERT_NE(f, nullptr);

	EXPECT_EQ(aref_readfield(str, f, 8, NULL), 0);
	EXPECT_STREQ(str, "");

	fclose(f);
}

TEST(TestCsv, escape)
{
	char str[24];
	FILE *f = fopen("tests/data/escape.csv", "r");

	aref_readfield(str, f, 24, NULL);
	EXPECT_STREQ(str, "Your comma, here");
	fscanf(f, "%*s\n");
	aref_readfield(str, f, 24, NULL);
	EXPECT_STREQ(str, "Normal quoted text");
	fscanf(f, "%*s\n");
	aref_readfield(str, f, 24, NULL);
	EXPECT_STREQ(str, "He says \"What?\"");
	fscanf(f, "%*s\n");
	aref_readfield(str, f, 24, NULL);
	EXPECT_STREQ(str, "\"Hello, world\"");
}

TEST(TestCsv, crlf)
{
	char str[8];
	char end;
	FILE *f = fopen("tests/data/crlf.csv", "r");
	ASSERT_NE(f, nullptr);

	aref_readfield(str, f, 8, &end);
	EXPECT_EQ(end, ',');
	aref_readfield(str, f, 8, &end);
	aref_readfield(str, f, 8, &end);
	EXPECT_STREQ(str, "Bob");
	EXPECT_EQ(end, ',');

	fclose(f);
}

TEST(TestCsv, toolong)
{
	char str[8];
	FILE *f = fopen("tests/data/toolong.csv", "r");
	ASSERT_NE(f, nullptr);

	EXPECT_EQ(aref_readfield(str, f, 8, NULL), 7);
	aref_readfield(str, f, 8, NULL);
	EXPECT_STREQ(str, "bwahaha");
	fclose(f);
}
