README
======

Program modified by Brent Grundman: 829460164

This package includes the following files.

|-- Driver.c [This is the driver program which will be used to invoke the MemoryManager.]
|-- MemoryManager.c [MemoryManager is implemented here. ~ Modified by Brent]
|-- MemoryManager.h [Header file declaring the function exposed from MemoryManager]
|-- Makefile [Written by Brent; compiles Driver.c and MemoryManager.c]
|-- README.txt [This file]

NOTES:
*Compiling will return two warnings.  These warnings do not make a difference.
*Added in MemoryManager output from example outputs.
*Spelling correction made from original output: Dirver corrected to Driver.

To compile:
    make
	-or-
    make build
	-or
    make all

To clean:
    make clean

To run:
    seedy <seed>

For example;
    seedy 1234

