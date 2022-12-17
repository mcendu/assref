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

#ifdef _WIN32

#include <stdio.h>
#include <stdlib.h>

#include <malloc.h> // <- alloca declared here instead of <alloca.h>
#include <stringapiset.h>

FILE *rep_fopen(const char *path, const char *mode)
{
	int pathlen = MultiByteToWideChar(CP_UTF8, 0, path, -1, NULL, 0);
	wchar_t utf16path[pathlen];
	// for some reason Win32 expects a UTF-16 mode string as well
	int modelen = MultiByteToWideChar(CP_UTF8, 0, mode, -1, NULL, 0);
	wchar_t utf16mode[modelen];

	if (MultiByteToWideChar(CP_UTF8, 0, path, -1, utf16path, pathlen) == 0)
		return NULL;
	if (MultiByteToWideChar(CP_UTF8, 0, path, -1, utf16mode, modelen) == 0)
		return NULL;
	return _wfopen(utf16path, utf16mode);
}

FILE *rep_freopen(const char *path, const char *mode, FILE *f)
{
	int pathlen = MultiByteToWideChar(CP_UTF8, 0, path, -1, NULL, 0);
	wchar_t utf16path[pathlen];
	// for some reason Win32 expects a UTF-16 mode string as well
	int modelen = MultiByteToWideChar(CP_UTF8, 0, mode, -1, NULL, 0);
	wchar_t utf16mode[modelen];

	if (MultiByteToWideChar(CP_UTF8, 0, path, -1, utf16path, pathlen) == 0)
		return NULL;
	if (MultiByteToWideChar(CP_UTF8, 0, path, -1, utf16mode, modelen) == 0)
		return NULL;
	return _wfreopen(utf16path, utf16mode, f);
}

#else
typedef void make_compiler_happy;
#endif /* _WIN32 */
