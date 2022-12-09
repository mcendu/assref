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

size_t aref_readfield(char *i, FILE *f, size_t size, char *last)
{
	char *bufend = i + size - 1; // leave space for null termination
	size_t wcount = 0;
	int c;

	while ((c = getc(f)) != EOF) {
		if (c == ',' || c == '\n')
			break;

		// discard <CR> as <CR> alone as newline is very uncommon nowadays
		// this also makes sure things won't break with <CR><LF> files on Unix
		if (i != bufend && c != '\r') {
			*i = (char)c;
			++i, ++wcount;
		} else {
			// silently discard further input
		}
	}

	*i = 0;
	if (last) *last = c;
	return wcount;
}

size_t aref_sreadfield(char *i, const char *j, size_t size, char *last)
{
	char *bufend = i + size - 1; // leave space for null termination
	size_t wcount = 0;
	int c;

	while ((c = *(j++)) != 0) {
		if (c == ',' || c == '\n')
			break;

		// discard <CR> as <CR> alone as newline is very uncommon nowadays
		// this also makes sure things won't break with <CR><LF> files on Unix
		if (i != bufend && c != '\r') {
			*i = (char)c;
			++i, ++wcount;
		} else {
			// silently discard further input
		}
	}

	*i = 0;
	if (last) *last = c;
	return wcount;
}
