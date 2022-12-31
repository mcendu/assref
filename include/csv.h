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

/* for offsetof(3), which almost all potential users of this header would use */
#include <stddef.h>

#include <stdio.h>

/**
 * @brief Defines how a CSV field is processed.
 *
 * @remarks The field definition format is optimized for parsing CSV data
 * into a C structure, with the AREF_FIELD macro and library built-in
 * callbacks supporting such a use.
 *
 * In C++, you can still use AREF_FIELD with standard-layout types (i.e.
 * any T where std::is_standard_layout<T> is true). If this function is
 * applied to non-standard-layout types, however, none of AREF_FIELD and
 * the built-in callbacks can be used, as offsetof are unusable on such
 * types. Instead, you should define extern "C" friend callbacks to load
 * data:
 *
 * @code
 * // Foo.h
 * class Foo {
 * private:
 *     int bar;
 *     // ...
 *     extern "C" friend int foo_load_field_bar(void *, const char *, size_t);
 *     // ...
 * }
 *
 * // csv/Foo.cpp
 * extern "C" int foo_load_field_bar(void *dst, const char *str, size_t)
 * {
 *     Foo *foo = dst;
 *     foo->bar = std::strtol(str, nullptr, 10);
 * }
 *
 * // ...
 *
 * static const aref_fielddef defs[] = {
 *     // ...
 *     { 0, load_field_bar, 0 }
 *     // ...
 * };
 * @endcode
 */
typedef struct aref_fielddef {
	/**
	 * @brief The offset of the destination relative to dst.
	 */
	size_t offset;
	/**
	 * @brief A callback determining how a field is processed.
	 */
	int (*process)(void *dst, const char *raw, size_t size);
	/**
	 * @brief Size of the destination in bytes.
	 */
	size_t size;
} aref_fielddef;

#ifdef __cplusplus
/**
 * @brief Instruct how a specific CSV field is processed.
 *
 * Do not use this macro if your class is not standard-layout. Instead,
 * you should define extern "C" friend functions of the class in question,
 * and put `{0, your_friend_function, 0}` in your definition list.
 */
#define AREF_FIELD(type, field, process_func, size) \
	(aref_fielddef{offsetof(type, field), (process_func), (size)})
/**
 * @brief End a CSV field definition. This macro _must_ be used at the
 * end of a list of CSV field definitions.
 */
#define AREF_FIELDDEF_END (aref_fielddef{0, NULL, 0})
#else
/**
 * @brief Instruct how a specific CSV field is processed.
 */
#define AREF_FIELD(type, field, process_func, size)   \
	{                                                 \
		offsetof(type, field), (process_func), (size) \
	}
/**
 * @brief End a CSV field definition. This macro _must_ be used at the
 * end of a list of CSV field definitions.
 */
#define AREF_FIELDDEF_END \
	{                     \
		0, NULL, 0        \
	}
#endif

#define AREF_CSV_ERROR -1    // irrecoverable error
#define AREF_CSV_OK 0        // general ok result
#define AREF_CSV_DONE 0      // reading complete
#define AREF_CSV_LINE 1      // a line has been read
#define AREF_CSV_MALFORMED 2 // line is malformed and should be discarded

#define AREF_CSV_NOTDONE(ret) ((ret) > 0)

/**
 * @brief Reads and processes a line of CSV.
 *
 * @param file File to read.
 * @param dst The destination to which data is written.
 * @param defs An AREF_FIELDDEF_END-terminated list of field definitions.
 * @return Zero if the line has been processed succesfully; non-zero otherwise.
 */
extern int aref_readcsvline(FILE *file, void *dst, const aref_fielddef *defs);

extern int AREF_FIELD_INT8(void *, const char *, size_t);
extern int AREF_FIELD_INT16(void *, const char *, size_t);
extern int AREF_FIELD_INT32(void *, const char *, size_t);
extern int AREF_FIELD_INT64(void *, const char *, size_t);
extern int AREF_FIELD_UINT8(void *, const char *, size_t);
extern int AREF_FIELD_UINT16(void *, const char *, size_t);
extern int AREF_FIELD_UINT32(void *, const char *, size_t);
extern int AREF_FIELD_UINT64(void *, const char *, size_t);
extern int AREF_FIELD_FLOAT(void *, const char *, size_t);
extern int AREF_FIELD_DOUBLE(void *, const char *, size_t);
extern int AREF_FIELD_STR(void *, const char *, size_t);

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
extern size_t aref_sreadfield(char *buffer, const char *string, size_t size,
							  char *end);

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
