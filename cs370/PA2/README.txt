README
======

Program written by Brent Grundman: 829460164

This package includes the following files.

|-- Checker.c [This program takes two command line arguments and checks if the latter is divisible by the former.]
|-- Coordinator.c [This program takes 5 command line arguments and checks if the last 4 are divisible by the first.]
|-- Makefile [Compiles Checker.c and Coordinator.c in two separate executables.]
|-- README.txt [This file]

NOTES:
*None

To compile:
	make

To clean:
	make clean

To run:
	./coordinator [numbers]

For example:
	./coordinator 1 2 3 4 5