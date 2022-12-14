src = [
	'csv.c',
	'db.c',
	'decode.c',
	'mappool.c',
]


hexchat_dep = dependency('hexchat-plugin', required: false)
sqlite3_dep = dependency('sqlite3')

lib_deps = [sqlite3_dep]

subdir('migrations')

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
	dependencies: lib_deps,
	include_directories: inc)
