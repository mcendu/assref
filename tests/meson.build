tests_src = [
	'csv.cpp',
	'db.cpp',
	'decode.cpp',
	'lua.cpp',
	'table.cpp',
]

has_cxx = add_languages('cpp', native: false, required: false)
gtest_dep = dependency('gtest', main: true, required: false)

if not (has_cxx and gtest_dep.found())
	warning('Required programs and libraries missing. Tests will not be built.')
	subdir_done()
endif

tests = executable('testassref', tests_src,
	dependencies: [dep, lua_dep, gtest_dep],
	install: false)

subdir('data')

test('gtest test', tests, protocol: 'gtest', timeout: 600)
