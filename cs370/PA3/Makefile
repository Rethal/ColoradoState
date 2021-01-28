#This Makefile compiles the Memory Manager and Driver for Brent Grundman's HW2
#  cc -c $(CFLAGS) main_01.c
#  cc main_01.o $(LDFLAGS) -o main_01
#
#  cc -c $(CFLAGS) main_2..c
#  cc main_02.o $(LDFLAGS) -o main_02

all:	coordinator checker

coordinator:	Coordinator.c
	gcc -o coordinator Coordinator.c

checker:	Checker.c
	gcc -o checker Checker.c

clean:
	rm -f *.o checker coordinator

tar:
	tar -cvf Grundman_Brenton_HW3.tar *.c Makefile README.txt

