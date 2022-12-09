gtest_dep = dependency('gtest', main: true, required: false)

if (gtest_dep.found())
	tests_src = [
		'csv.cpp',
	]

	tests = executable('testassref', tests_src,
		dependencies: [dep, gtest_dep],
		install: false)

	subdir('data')

	test('gtest test', tests, protocol: 'gtest', timeout: 3600)
else
	warning('GoogleTest not found. Tests will not be built.')
endif
