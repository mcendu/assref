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

#ifndef _AREF__DECODE_H
#define _AREF__DECODE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <mappool.h>
#include <sqlite3.h>
#include <stdio.h>

/**
 * @brief Decodes a mappool entry from CSV.
 *
 * @param entry The mappool entry to which data is written.
 * @param file A file to read data from.
 */
extern void aref_decodepoolentry(aref_mapdata *entry, FILE *file);

/**
 * @brief Loads a mappool from CSV into the database.
 * @param file The file to read data from.
 * @return The number of entries read.
 */
extern int aref_loadmappool(sqlite3 *, FILE *file);

#ifdef __cplusplus
}
#endif

#endif /* !_AREF__DECODE_H */
