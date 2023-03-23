hexchat_plugin_src = [
	'commands.c',
	'help.c',
	'load.c',
	'main.c',
	'mappool.c',
	'playerlist.c',
	'win32.c',
]

hexchat_plugin = shared_module('assref_hexchat', hexchat_plugin_src,
	include_directories: inc,
	dependencies: [lib_deps, dep, hexchat_dep],
	install: true,
	install_dir: get_option('libdir') / 'hexchat/plugins')
