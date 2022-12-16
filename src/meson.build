src = [
	'csv.c',
	'db.c',
	'decode.c',
	'fieldtypes.c',
	'mappool.c',
	'playerlist.c',
]

hexchat_dep = dependency('hexchat-plugin', required: false)
sqlite3_dep = dependency('sqlite3', static: get_option('static_sqlite'))

lib_deps = [sqlite3_dep]

subdir('migrations')

lib = static_library('assref', src,
	include_directories: inc,
	dependencies: lib_deps)
dep = declare_dependency(
	link_with: lib,
	dependencies: lib_deps,
	include_directories: inc)

if hexchat_dep.found()
	subdir('hexchat')
endif
