src = [
	'csv.c',
	'decode.c',
	'lua/mappool.c',
	'mappool.c',
	'table.c',
]

lua_dep = dependency(get_option('lua'))

lib = shared_library('assref', src,
	include_directories: inc,
	install: true,
	install_dir: get_option('libdir') / 'lua',
	dependencies: lua_dep)
dep = declare_dependency(
	link_with: lib,
	include_directories: inc)
