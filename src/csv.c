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

#include <stdio.h>
#include <stdlib.h>

#include <textio.h>

int aref_readcsvline(FILE *f, void *dst, const aref_fielddef *defs)
{
	if (aref_eof(f))
		return AREF_CSV_DONE;

	char buf[128];
	char last = 0;

	for (const aref_fielddef *field = defs; field->process != NULL; ++field) {
		if (last == '\n' || last == EOF)
			return AREF_CSV_MALFORMED; // too few fields
		aref_readfield(buf, f, 128, &last);

		void *dst_field = (void *)((char *)dst + field->offset);
		int result = field->process(dst_field, buf, field->size);
		if (result == AREF_CSV_MALFORMED) {
			aref_fskipline(f);
		}
		if (result != AREF_CSV_OK) {
			// decoding error
			return result;
		}
	}

	if (last != '\n' && last != EOF) {
		aref_fskipline(f);
		return AREF_CSV_MALFORMED; // too many fields
	}
	return AREF_CSV_LINE;
}

/**
 * @param c The character read.
 * @param it A pointer to somewhere in a buffer.
 * @param end The end of the buffer pointed to by it.
 * @param quote Indicates whether a field is quoted.
 * @param lastread The character read before c.
 * @param count A counter that counts the number of bytes written.
 * @return 0 if no further reading is desired; 1 otherwise.
 */
static inline int parse_char(int *c, char **it, char *end, int *quote,
							 char lastread, size_t *count)
{
	if (*c == EOF || *c == 0)
		return 0;

	if (*c == '"' && lastread == 0) {
		*quote = 1;
		*c = ' ';
		return 1;
	}

	if (*quote) {
		if (lastread == '"') {
			if (*c == ',' || *c == '\n') {
				return 0;
			}
		} else if (*c == '"') {
			return 1; // deal with it later
		}
	} else if (*c == ',' || *c == '\n') {
		return 0;
	}

	if (*it != end) {
		**it = (char)*c;
		++(*it), ++(*count);
	} else {
		// silently discard further input
	}

	// HACK: set character read to space after reading two consecutive
	// quotes to prevent confusion
	if (lastread == '"' && *c == '"') {
		*c = ' ';
	}

	return 1;
}

size_t aref_readfield(char *i, FILE *f, size_t size, char *last)
{
	char *bufend = i + size - 1; // leave space for null termination
	size_t wcount = 0;
	int c;
	int q = 0;
	char lastread = 0;

	while ((c = aref_getc(f)), 1) {
		if (!parse_char(&c, &i, bufend, &q, lastread, &wcount))
			break;
		lastread = c;
	}

	*i = 0;
	if (last)
		*last = c;
	return wcount;
}

size_t aref_sreadfield(char *i, const char *j, size_t size, char *last)
{
	char *bufend = i + size - 1; // leave space for null termination
	size_t wcount = 0;
	int c;
	int q = 0;
	char lastread = 0;

	while ((c = *(j++))) {
		if (!parse_char(&c, &i, bufend, &q, lastread, &wcount))
			break;
		lastread = c;
	}

	*i = 0;
	if (last)
		*last = c;
	return wcount;
}

size_t aref_fskipline(FILE *f)
{
	size_t result = 0;
	for (char c = aref_getc(f); c != '\n' && c != EOF; c = aref_getc(f))
		++result;
	return result + 1;
}

int aref_eof(FILE *f)
{
	int c;
	// gobble up empty lines
	while ((c = aref_getc(f)) == '\n')
		;
	if (c == EOF)
		return 1;
	ungetc(c, f);
	return 0;
}
