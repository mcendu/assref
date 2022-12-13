src = [
	'csv.c',
	'decode.c',
	'mappool.c',
	'table.c',
]


lua_dep = dependency(get_option('lua'), required: false)
hexchat_dep = dependency('hexchat-plugin', required: false)
sqlite3_dep = dependency('sqlite3', static: true)

lib_deps = [sqlite3_dep]

subdir('migrations')

if lua_dep.found()
	lib_deps += lua_dep
	subdir('lua')
endif

if hexchat_dep.found()
	lib_deps += hexchat_dep
	subdir('hexchat')
endif

lib = shared_library('assref', src,
	include_directories: inc,
	install: true,
	install_dir: get_option('libdir') / 'lua',
	dependencies: lib_deps)
dep = declare_dependency(
	link_with: lib,
	include_directories: inc)
