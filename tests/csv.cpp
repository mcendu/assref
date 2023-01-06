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

#include <csv.h>

#include <cstdint>
#include <cstdio>
#include <cstdlib>

#include <gtest/gtest.h>

extern "C" struct test_struct {
	char str[8];
	int32_t integer;
	float real;
};

const aref_fielddef test_fields[]
	= {AREF_FIELD(test_struct, str, AREF_FIELD_STR, 8),
	   AREF_FIELD(test_struct, integer, AREF_FIELD_INT32, 0),
	   AREF_FIELD(test_struct, real, AREF_FIELD_FLOAT, 0), AREF_FIELDDEF_END};

TEST(TestCsv, line)
{
	test_struct t;
	FILE *f = fopen("tests/data/line.csv", "r");
	ASSERT_NE(f, nullptr);

	EXPECT_EQ(aref_readcsvline(f, &t, test_fields), AREF_CSV_LINE);
	EXPECT_STREQ(t.str, "rc1");
	EXPECT_EQ(t.integer, 3861836);
	EXPECT_EQ(t.real, 3.0f);

	EXPECT_EQ(aref_readcsvline(f, &t, test_fields), AREF_CSV_LINE);
	EXPECT_EQ(t.real, 3.1415926f);

	EXPECT_EQ(aref_readcsvline(f, &t, test_fields), AREF_CSV_MALFORMED);
	EXPECT_EQ(aref_readcsvline(f, &t, test_fields), AREF_CSV_MALFORMED);
	EXPECT_EQ(aref_readcsvline(f, &t, test_fields), AREF_CSV_MALFORMED);
	EXPECT_EQ(aref_readcsvline(f, &t, test_fields), AREF_CSV_MALFORMED);
	EXPECT_EQ(aref_readcsvline(f, &t, test_fields), AREF_CSV_LINE);

	EXPECT_EQ(aref_readcsvline(f, &t, test_fields), AREF_CSV_DONE);

	fclose(f);
}

const aref_fielddef test_fields_notrailing[] = {
	AREF_FIELD(test_struct, str, AREF_FIELD_STR, 8),
	AREF_FIELD(test_struct, integer, AREF_FIELD_INT32, 0), AREF_FIELDDEF_END};

TEST(TestCsv, notrailinglf)
{
	test_struct t;
	FILE *f = fopen("tests/data/notrailing.csv", "rb");

	EXPECT_EQ(aref_readcsvline(f, &t, test_fields_notrailing), AREF_CSV_LINE);
	EXPECT_EQ(aref_readcsvline(f, &t, test_fields_notrailing), AREF_CSV_LINE);

	fclose(f);
}

TEST(TestCsv, fieldstrBoundcheck)
{
	const int bufsize = 8;
	const char *toolong = "To be or not to be, that is the question.";
	const char *exactly_bufsize_except_ending_null = "Required";
	const char *just_the_right_size = "Inquiry";
	char *dststr = new char[bufsize];
	void *dst = dststr;
	ASSERT_EQ(AREF_FIELD_STR(dst, toolong, bufsize), AREF_CSV_MALFORMED);
	ASSERT_EQ(AREF_FIELD_STR(dst, exactly_bufsize_except_ending_null, bufsize),
			  AREF_CSV_MALFORMED);

	dststr[7] = ' ';
	ASSERT_EQ(AREF_FIELD_STR(dst, just_the_right_size, bufsize), AREF_CSV_OK);
	ASSERT_STREQ(just_the_right_size, dststr);
	delete[] dststr;
}

TEST(TestCsv, fieldbasic)
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

TEST(TestCsv, fieldmultiline)
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

TEST(TestCsv, fieldempty)
{
	char str[8];
	FILE *f = fopen("tests/data/empty.csv", "r");
	ASSERT_NE(f, nullptr);

	EXPECT_EQ(aref_readfield(str, f, 8, NULL), 0);
	EXPECT_STREQ(str, "");

	fclose(f);
}

TEST(TestCsv, fieldescape)
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
	EXPECT_STREQ(str, "Here is a\nline break");
	fscanf(f, "%*s\n");
	aref_readfield(str, f, 24, NULL);
	EXPECT_STREQ(str, "He says \"What?\"");
	fscanf(f, "%*s\n");
	aref_readfield(str, f, 24, NULL);
	EXPECT_STREQ(str, "\"Hello, world\"");
	fscanf(f, "%*s\n");
	aref_readfield(str, f, 24, NULL);
	EXPECT_STREQ(str, "\"");
	fscanf(f, "%*s\n");
	aref_readfield(str, f, 24, NULL);
	EXPECT_STREQ(str, ",");

	fclose(f);
}

TEST(TestCsv, fieldcrlf)
{
	char str[8];
	char end;
	// "b" in mode string disables newline conversion on Windows
	FILE *f = fopen("tests/data/crlf.csv", "rb");
	ASSERT_NE(f, nullptr);

	aref_readfield(str, f, 8, &end);
	EXPECT_EQ(end, ',');
	aref_readfield(str, f, 8, &end);
	aref_readfield(str, f, 8, &end);
	EXPECT_STREQ(str, "Bob");
	EXPECT_EQ(end, ',');

	fclose(f);
}

TEST(TestCsv, fieldnotrailinglf)
{
	char str[8];
	char end;
	FILE *f = fopen("tests/data/notrailing.csv", "rb");

	aref_readfield(str, f, 8, &end);
	aref_readfield(str, f, 8, &end);
	aref_readfield(str, f, 8, &end);
	aref_readfield(str, f, 8, &end);
	EXPECT_EQ(end, EOF);
	EXPECT_STREQ(str, "175");

	fclose(f);
}

TEST(TestCsv, fieldtoolong)
{
	char str[8];
	FILE *f = fopen("tests/data/toolong.csv", "r");
	ASSERT_NE(f, nullptr);

	EXPECT_EQ(aref_readfield(str, f, 8, NULL), 7);
	aref_readfield(str, f, 8, NULL);
	EXPECT_STREQ(str, "bwahaha");
	EXPECT_EQ(aref_readfield(str, f, 8, NULL), 7);
	aref_readfield(str, f, 8, NULL);
	EXPECT_STREQ(str, "Nice.");
	fclose(f);
}

TEST(TestCsv, skip)
{
	char str[8];
	char end;
	FILE *f = fopen("tests/data/multiline.csv", "r");
	ASSERT_NE(f, nullptr);

	aref_readfield(str, f, 8, &end);
	EXPECT_STREQ(str, "Alice");
	aref_fskipline(f);
	aref_readfield(str, f, 8, &end);
	EXPECT_STREQ(str, "Bob");

	fclose(f);
}
