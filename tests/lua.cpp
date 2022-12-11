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

#include <gtest/gtest.h>
#include <luaapi.h>

#include <mappool.h>

#include <lua.hpp>

class TestLuaApi : public ::testing::Test
{
  protected:
	lua_State *L;

	void SetUp() override
	{
		L = luaL_newstate();
		luaL_openlibs(L);
	}

	void TearDown() override
	{
		lua_close(L);
	}
};

const char script_mappool_index[]
	= "local testpool = mappool.load('tests/data/pool.csv')\n"
	  "return testpool['rc4']\n";

const char script_mappool_newindex[]
	= "local testpool = mappool.create()\n"
	  "testpool['warm1'] = { beatmapid = 75, mode = 0 }\n"
	  "return testpool";

TEST_F(TestLuaApi, mappool)
{
	int luaerror;

	lua_pushcfunction(L, luaopen_assref_mappool);
	lua_pushstring(L, "assref.mappool");
	lua_call(L, 1, 1);
	lua_setglobal(L, "mappool");

	luaerror = luaL_dostring(L, script_mappool_index);
	EXPECT_EQ(luaerror, 0);
	if (luaerror == 0) {
		size_t top = lua_gettop(L);
		lua_getfield(L, top, "beatmapid");
		lua_Integer poolid = lua_tointeger(L, -1);
		EXPECT_EQ(poolid, 2717089);
	}

	luaerror = luaL_dostring(L, script_mappool_newindex);
	EXPECT_EQ(luaerror, 0);
	if (luaerror == 0) {
		size_t top = lua_gettop(L);
		aref_mappool *testpool = (aref_mappool *)lua_touserdata(L, top);
		aref_mapdata *discoprince = aref_findmap(testpool, "warm1");
		EXPECT_NE(discoprince, nullptr);
		if (discoprince != nullptr) {
			EXPECT_EQ(discoprince->mode, 0);
			EXPECT_EQ(discoprince->beatmapid, 75);
		}
	}
}
