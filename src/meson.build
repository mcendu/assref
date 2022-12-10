src = [
	'csv.c',
	'decode.c',
	'lua/mappool.c',
	'mappool.c',
	'table.c',
]

lua_dep = dependency('lua5.1')

lib = shared_library('assref', src,
	include_directories: inc,
	install: true,
	dependencies: lua_dep)
dep = declare_dependency(
	link_with: lib,
	include_directories: inc)
