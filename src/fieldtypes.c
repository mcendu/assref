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

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

/* All functions here need to have an identical signature */
#pragma GCC diagnostic ignored "-Wunused-parameter"

int AREF_FIELD_INT8(void *dstptr, const char *raw, size_t size)
{
	int8_t *dst = dstptr;
	char *endptr;

	long cvt = strtol(raw, &endptr, 0);
	if (*endptr != 0)
		return AREF_CSV_MALFORMED;

	if (cvt > INT8_MAX || cvt < INT8_MIN)
		return AREF_CSV_MALFORMED;

	*dst = (int8_t)cvt;
	return AREF_CSV_OK;
}

int AREF_FIELD_INT16(void *dstptr, const char *raw, size_t size)
{
	int16_t *dst = dstptr;
	char *endptr;

	long cvt = strtol(raw, &endptr, 0);
	if (*endptr != 0)
		return AREF_CSV_MALFORMED;

	if (cvt > INT16_MAX || cvt < INT16_MIN)
		return AREF_CSV_MALFORMED;

	*dst = (int16_t)cvt;
	return AREF_CSV_OK;
}

int AREF_FIELD_INT32(void *dstptr, const char *raw, size_t size)
{
	int32_t *dst = dstptr;
	char *endptr;

	long cvt = strtol(raw, &endptr, 0);
	if (*endptr != 0)
		return AREF_CSV_MALFORMED;

	if (cvt > INT32_MAX || cvt < INT32_MIN)
		return AREF_CSV_MALFORMED;

	*dst = (int32_t)cvt;
	return AREF_CSV_OK;
}

int AREF_FIELD_INT64(void *dstptr, const char *raw, size_t size)
{
	int64_t *dst = dstptr;
	char *endptr;

	long long cvt = strtol(raw, &endptr, 0);
	if (*endptr != 0)
		return AREF_CSV_MALFORMED;

	if (cvt > INT64_MAX || cvt < INT64_MIN)
		return AREF_CSV_MALFORMED;

	*dst = (int64_t)cvt;
	return AREF_CSV_OK;
}

int AREF_FIELD_UINT8(void *dstptr, const char *raw, size_t size)
{
	uint8_t *dst = dstptr;
	char *endptr;

	*dst = (uint8_t)strtol(raw, &endptr, 0);
	if (*endptr != 0)
		return AREF_CSV_MALFORMED;

	return AREF_CSV_OK;
}

int AREF_FIELD_UINT16(void *dstptr, const char *raw, size_t size)
{
	uint16_t *dst = dstptr;
	char *endptr;

	*dst = (uint16_t)strtol(raw, &endptr, 0);
	if (*endptr != 0)
		return AREF_CSV_MALFORMED;

	return AREF_CSV_OK;
}

int AREF_FIELD_UINT32(void *dstptr, const char *raw, size_t size)
{
	uint32_t *dst = dstptr;
	char *endptr;

	*dst = (uint32_t)strtol(raw, &endptr, 0);
	if (*endptr != 0)
		return AREF_CSV_MALFORMED;

	return AREF_CSV_OK;
}

int AREF_FIELD_UINT64(void *dstptr, const char *raw, size_t size)
{
	uint64_t *dst = dstptr;
	char *endptr;

	*dst = (uint64_t)strtol(raw, &endptr, 0);
	if (*endptr != 0)
		return AREF_CSV_MALFORMED;

	return AREF_CSV_OK;
}

int AREF_FIELD_FLOAT(void *dst, const char *raw, size_t size)
{
	float *result = dst;
	char *endptr;

	*result = strtof(raw, &endptr);
	if (*endptr != 0)
		return AREF_CSV_MALFORMED;

	return AREF_CSV_OK;
}

int AREF_FIELD_DOUBLE(void *dst, const char *raw, size_t size)
{
	double *result = dst;
	char *endptr;

	*result = strtod(raw, &endptr);
	if (*endptr != 0)
		return AREF_CSV_MALFORMED;

	return AREF_CSV_OK;
}

int AREF_FIELD_STR(void *dst, const char *raw, size_t size)
{
	if (strlen(raw) + 1 > size)
		return AREF_CSV_MALFORMED;

	char *result = dst;
	strcpy(result, raw);
	return AREF_CSV_OK;
}
