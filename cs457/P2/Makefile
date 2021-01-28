CC = g++ -Wall -std=c++11
CFLAGS = -c -I.
OFLAGS = -o

awget: awget.o sharedfunctions.o
	$(CC) awget.o sharedfunctions.o $(OFLAGS) awget

awget.o: awget.cpp awget.h
	$(CC) $(CFLAGS) awget.cpp
	
ss: ss.o sharedfunctions.o
	$(CC) ss.o sharedfunctions.o $(OFLAGS) ss

ss.o: ss.cpp
	$(CC) $(CFLAGS) ss.cpp

sharedfunctions.o: sharedfunctions.cpp
	$(CC) $(CFLAGS) sharedfunctions.cpp

clean:
	rm -r *.o awget ss

