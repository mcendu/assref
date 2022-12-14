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

/**
 * @brief CSV utilities
 *
 * This header defines functions for reading data from comma-separated
 * values (CSV) files.
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

/**
 * @brief Seek to the next line of a file.
 *
 * @param file The file to manipulate.
 * @return Number of bytes skipped.
 */
extern size_t aref_fskipline(FILE *file);

/**
 * @brief Check if no more data is available.
 *
 * @param file The file to check.
 */
extern int aref_eof(FILE *file);

#ifdef __cplusplus
}
#endif

#endif /* !_AREF__CSV_H */
