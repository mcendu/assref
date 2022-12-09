#!/usr/bin/env python3
'''
Usage: copy.py SOURCE... DIRECTORY

Simplified non-standard implementation of cp(1). This is used so that
parts of the build process can be completed on Windows natively.
'''

from sys import argv
import os

dirpos = len(argv) - 1
directory = argv[dirpos]

for i in range(1, dirpos):
	path = argv[i]
	name = os.path.basename(path)
	fin = open(path, 'rb')
	fout = open(os.path.join(directory, name), 'wb')
	while fout.write(fin.read(4096)):
		pass
