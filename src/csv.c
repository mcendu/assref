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

/**
 * @param c The character read.
 * @param it A pointer to somewhere in a buffer.
 * @param end The end of the buffer pointed to by it.
 * @param quote Indicates whether a field is quoted.
 * @param lastread The character read before c.
 * @param count A counter that counts the number of bytes written.
 * @return 0 if no further reading is desired; 1 otherwise.
 */
static inline int read_char(int *c, char **it, char *end, int *quote,
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

	if (*it != end && *c != '\r') {
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

	while ((c = getc(f))) {
		if (!read_char(&c, &i, bufend, &q, lastread, &wcount))
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
		if (!read_char(&c, &i, bufend, &q, lastread, &wcount))
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
	for (char c = getc(f); c != '\n' && c != EOF; c = getc(f))
		++result;
	return result + 1;
}

int aref_eof(FILE *f)
{
	int c = getc(f);
	if (c == EOF)
		return 1;
	ungetc(c, f);
	return 0;
}
