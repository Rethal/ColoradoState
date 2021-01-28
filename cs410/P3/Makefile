all: raytracer

raytracer: PlyReader.o Camera.o Raycast.o PPMPrint.o main.cpp
	g++ -Wall -std=c++11 -I. PlyReader.o Camera.o Raycast.o PPMPrint.o main.cpp -o raytracer

PlyReader.o: PlyReader.cpp PlyReader.h
	g++ -Wall -std=c++11 -I. -c PlyReader.cpp

Camera.o: Camera.cpp Camera.h
	g++ -Wall -std=c++11 -I. -c Camera.cpp

Raycast.o: Raycast.cpp Raycast.h
	g++ -Wall -std=c++11 -I. -c Raycast.cpp

PPMPrint.o: PPMPrint.cpp PPMPrint.h
	g++ -Wall -std=c++11 -I. -c PPMPrint.cpp

clean:
	rm -f *.o raytracer

tar:
	tar -cvf raytracer.tar *.cpp *.h *.txt *.ply Makefile

