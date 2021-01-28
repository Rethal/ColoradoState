README
======

Program written by Brent Grundman: 829460164

This package includes the following files.

|-- main.cpp [This program drives the process program]
|-- process.h [This is the program definition for process program]
|-- process.cpp [Shows the different ways to organize a group of given processes]
|-- Makefile [Compiles process.cpp and main.cpp into an executable: scheduler]
|-- README.txt [This file]
|-- in.txt [example .txt file, used to generate output]
|-- output [example .txt file, overwritten on program use]

NOTES:
*None

To compile:
	make

To clean:
	make clean

To run:
	./scheduler input_file seed

For example:
	./scheduler in.txt 12345