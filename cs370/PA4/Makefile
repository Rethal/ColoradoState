#This Makefile compiles the Process and Main for Brent Grundman's HW4
#  cc -c $(CFLAGS) main_01.c
#  cc main_01.o $(LDFLAGS) -o main_01
#
#  cc -c $(CFLAGS) main_2..c
#  cc main_02.o $(LDFLAGS) -o main_02

	#gcc -o process.cpp main.cpp

all:	final

final: process.o main.cpp
	g++ -Wall -g -std=c++11 -I. process.o main.cpp -o scheduler

process.o: process.cpp process.h
	g++ -Wall -g -std=c++11 -I. -c process.cpp

clean:
	rm -f *.o scheduler

tar:
	tar -cvf Grundman_Brenton_HW4.tar *.cpp *.h Makefile README.txt in.txt output

