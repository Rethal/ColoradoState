CC = g++
INC = -Wall -g -I.

Anima: main.o
	$(CC) main.o -o Animal

main.o: main.cpp Animal.h
	$(CC) $(INC) main.cpp -c

clean:
	rm *.o Animal
