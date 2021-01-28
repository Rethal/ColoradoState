all: encryption

encryption: encrypt.o main.cpp
	g++ -Wall -std=c++11 -I. encrypt.o main.cpp -o encrypt

encrypt.o: encrypt.cpp encrypt.h
	g++ -Wall -std=c++11 -I. -c encrypt.cpp

clean:
	rm -f *.o encrypt

tar:
	tar -cvf encrypt.tar *.cpp *.h README.txt Makefile

