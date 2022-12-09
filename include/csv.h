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

/**
 * @brief CSV parsing routines
 *
 * This header defines functions for manipulating structured data in
 * comma-separated values (CSV).
 */
#ifndef _AREF__CSV_H
#define _AREF__CSV_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>

/**
 * @brief Reads a single field from a file.
 *
 * The function takes the size of the buffer as an argument.
 *
 * @param buffer The buffer to which the read data is written.
 * @param file The file from which data is read.
 * @param size The size of the buffer.
 * @param end If not NULL, the last character read is written here.
 * @return Number of bytes read.
 */
extern size_t aref_readfield(char *buffer, FILE *file, size_t size, char *end);

/**
 * @brief Reads a single field from a null-terminated string.
 *
 * @param buffer The buffer to which the read data is written.
 * @param str The string from which data is read.
 * @param size The size of the buffer.
 * @param end If not NULL, the last character read is written here.
 * @return Number of bytes read.
 */
extern size_t aref_sreadfield(char *buffer, const char *string, size_t size, char *end);

#ifdef __cplusplus
}
#endif

#endif /* !_AREF__CSV_H */
