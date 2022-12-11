--[[ SPDX-License-Identifier: MIT
Copyright (C) 2022 McEndu et al.

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to
deal in the Software without restriction, including without limitation the
rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
sell copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice
(including the next paragraph) shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
DEALINGS IN THE SOFTWARE.
]]

hexchat.register("AssRef", "0.1", "osu! referee's robotic assistant")

local mappool = require("assref.mappool");

CurrentMappool = nil

-- load preferences
local function loadPreferences()
	if hexchat.pluginprefs.mappool ~= nil then
		local mappoolpath = hexchat.pluginprefs.mappool
		CurrentMappool = mappool.load(mappoolpath)
	else
		CurrentMappool = nil
	end
end

loadPreferences()

local help = {
	get = "Usage: AREF GET <preference>, get current value of a preference",
	set = "Usage: AREF SET <preference> <value>, set preferences",
	unset = "Usage: AREF UNSET <preference>, forget a plugin preference",
	setmap = "Usage: AREF SETMAP <code>, set current beatmap",
	help = [=[
AssRef commands:

	GET	HELP	SET	SETMAP
]=]
}

local commands = {
	get = function(word, word_eol)
		local key = word[3]
		if key == nil then
			hexchat.emit_print("Private Message", "AssRef",
				"no option specified")
			return hexchat.EAT_NONE
		end
		if hexchat.pluginprefs[key] ~= nil then
			print(("%s = %s"):format(key, hexchat.pluginprefs[key]))
		end
	end,
	set = function(word, word_eol)
		local key = word[3]
		if key == nil then
			hexchat.emit_print("Private Message", "AssRef",
				"no option specified")
			return
		end
		local value = word_eol[4]
		if value == nil then
			hexchat.emit_print("Private Message", "AssRef",
				"no option value specified; use /AREF UNSET to clear an option")
			return
		end
		hexchat.pluginprefs[key] = value
		loadPreferences()
	end,
	unset = function(word, word_eol)
		local key = word[3]
		if key == nil then
			hexchat.emit_print("Private Message", "AssRef",
				"no option specified")
			return
		end
		hexchat.pluginprefs[key] = nil
		loadPreferences()
	end,
	setmap = function(word, word_eol)
		local mapcode = string.lower(word_eol[3])
		local map = CurrentMappool[mapcode]
		if map == nil then
			hexchat.emit_print("Private Message", "AssRef",
				"beatmap not in mappool")
		else
			hexchat.command(("say !mp map %d %d"):format(map.beatmapid, map.mode))
		end
	end,
	help = function(word, word_eol)
		local command = word[3]
		if command == nil then
			command = "help"
		end
		if help[command] == nil then
			command = "help"
		end
		print(help[command])
	end
}

hexchat.hook_command("aref",
	function(word, word_eol)
		if word[2] == nil then
			hexchat.emit_print("Private Message", "AssRef",
				"no subcommand specified")
			return hexchat.EAT_PLUGIN
		end
		local command = string.lower(word[2])
		if commands[command] == nil then
			hexchat.emit_print("Private Message", "AssRef",
				("not an AssRef subcommand: %s"):format(command))
			return hexchat.EAT_PLUGIN
		end
		commands[command](word, word_eol)
		return hexchat.EAT_PLUGIN
	end,
	help.help)
