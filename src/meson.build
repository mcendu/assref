src = [
	'csv.c',
	'db.c',
	'decode.c',
	'mappool.c',
]

mod_src = src

hexchat_dep = dependency('hexchat-plugin', required: false)
sqlite3_dep = dependency('sqlite3', static: get_option('static_sqlite'))

lib_deps = [sqlite3_dep]
mod_deps = lib_deps

subdir('migrations')

if hexchat_dep.found()
	mod_deps += hexchat_dep
	subdir('hexchat')
endif

lib = shared_library('assref', src,
	include_directories: inc,
	dependencies: lib_deps)
dep = declare_dependency(
	link_with: lib,
	dependencies: lib_deps,
	include_directories: inc)

mod_deps = shared_module('assref_hexchat', mod_src,
	include_directories: inc,
	dependencies: mod_deps,
	install: true,
	install_dir: get_option('libdir') / 'hexchat/plugins')
