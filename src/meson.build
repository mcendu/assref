src = [
	'csv.c',
	'db.c',
	'decode.c',
	'fieldtypes.c',
	'mappool.c',
	'match.c',
	'playerlist.c',
	'textio.c',
]

hexchat_dep = dependency('hexchat-plugin',
	required: get_option('with_hexchat'))
sqlite3_dep = dependency('sqlite3', static: get_option('with_static_sqlite'))

lib_deps = [sqlite3_dep]

subdir('migrations')

lib = static_library('assref', src,
	include_directories: inc,
	dependencies: lib_deps)
dep = declare_dependency(
	link_with: lib,
	dependencies: lib_deps,
	include_directories: inc)

if get_option('with_hexchat')
	subdir('hexchat')
endif
