testdata_src = [
	'basic.csv',
	'crlf.csv',
	'empty.csv',
	'escape.csv',
	'getc.txt',
	'line.csv',
	'multiline.csv',
	'notrailing.csv',
	'players.csv',
	'pool.csv',
	'poolentry.csv',
	'toolong.csv',
]

testdata = custom_target('testdata',
	input: testdata_src,
	output: testdata_src,
	command: [cp, '@INPUT@', '@BUILD_ROOT@/tests/data/'],
	install: false,
	build_by_default: true)
