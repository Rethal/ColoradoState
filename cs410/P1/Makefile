all: model

model: plyHeader.o main.cpp
	g++ -Wall -std=c++11 -I. plyHeader.o main.cpp -o geonorm

plyHeader.o: plyHeader.cpp plyHeader.h
	g++ -Wall -std=c++11 -I. -c plyHeader.cpp

clean:
	rm -f *.o geonorm

tar:
	tar -cvf geonorm.tar *.cpp *.h README.txt Makefile

