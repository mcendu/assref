project('assref', 'c',
	meson_version: '>=0.55.0',
	license: 'MIT',
	default_options: [
		'c_std=c11',
		'warning_level=3'
	])

cp = find_program('cp', 'build/copy.py', required: false)

subdir('include')
subdir('src')
subdir('tests')
