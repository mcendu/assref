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

#include <errno.h>
#include <stdio.h>
#include <string.h>

#include <lua.h>
#include <lauxlib.h>

#include <decode.h>
#include <mappool.h>

/**
 * @brief Pushes a new mappool object onto the Lua interpreter stack.
 *
 * @param L Lua interpreter state.
 * @return The newly-created mappool object.
 */
static aref_mappool *create_mappool(lua_State *L)
{
	aref_mappool *mappool = lua_newuserdata(L, sizeof(aref_mappool));
	aref_initmappool(mappool);

	luaL_getmetatable(L, "assref_mappool");
	lua_setmetatable(L, -2);

	return mappool;
}

/**
 * mappool.create()
 */
int areflua_mappool_create(lua_State *L)
{
	create_mappool(L);
	return 1;
}

/**
 * metatable(mappool).__gc(mappool)
 */
int areflua_mappool_destroy(lua_State *L)
{
	aref_mappool *mappool = lua_touserdata(L, 1);
	aref_freemappool(mappool);
	return 0;
}

/**
 * metatable(mappool).__index(mappool, key)
 */
int areflua_mappool_index(lua_State *L)
{
	aref_mappool *mappool = lua_touserdata(L, 1);
	const char *mapcode = lua_tostring(L, 2);

	aref_mapdata *map = aref_findmap(mappool, mapcode);

	if (map == NULL) {
		lua_pushnil(L);
	} else {
		lua_createtable(L, 0, 2);
		lua_pushinteger(L, map->beatmapid);
		lua_setfield(L, 3, "beatmapid");
		lua_pushinteger(L, map->mode);
		lua_setfield(L, 3, "mode");
	}

	return 1;
}

/**
 * mappool.load(file)
 */
int areflua_mappool_loadfromfile(lua_State *L)
{
	int argc = lua_gettop(L);
	if (argc != 1) {
		lua_pushstring(L, "this function only takes a single argument");
		lua_error(L);
	}
	if (!lua_isstring(L, 1)) {
		lua_pushstring(L, "path must be a string");
		lua_error(L);
	}

	const char *path = lua_tostring(L, 1);
	FILE *file = fopen(path, "r");

	if (file == NULL) {
		lua_pushnil(L);
		return 1;
	}

	aref_mappool *mappool = create_mappool(L);
	aref_loadmappool(mappool, file);
	fclose(file);

	return 1;
}

/**
 * require("assref.mappool")
 * loader(modname)
 */
int luaopen_assref_mappool(lua_State *L)
{
	const int argc = lua_gettop(L);

	if (!luaL_newmetatable(L, "assref_mappool"))
		return 1; // the already created table

	lua_pushcfunction(L, areflua_mappool_create);
	lua_setfield(L, argc + 1, "create");
	lua_pushcfunction(L, areflua_mappool_loadfromfile);
	lua_setfield(L, argc + 1, "load");
	lua_pushcfunction(L, areflua_mappool_index);
	lua_setfield(L, argc + 1, "__index");
	lua_pushcfunction(L, areflua_mappool_destroy);
	lua_setfield(L, argc + 1, "__gc");

	return 1;
}
