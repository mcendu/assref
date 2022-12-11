gtest_dep = dependency('gtest', main: true, required: false)

if (gtest_dep.found() and add_languages('cpp', native: false, required: false))
	tests_src = [
		'csv.cpp',
		'decode.cpp',
		'lua.cpp',
		'table.cpp',
	]

	tests = executable('testassref', tests_src,
		dependencies: [dep, lua_dep, gtest_dep],
		install: false)

	subdir('data')

	test('gtest test', tests, protocol: 'gtest', timeout: 600)
else
	warning('Required programs and libraries missing. Tests will not be built.')
endif
