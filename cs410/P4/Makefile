all: raytracer

raytracer: Camera.o Raytrace.o PPMPrint.o Model.o MatLib.o main.cpp
	g++ -Wall -std=c++11 -I. Camera.o Raytrace.o PPMPrint.o Model.o MatLib.o main.cpp -o raytracer

Camera.o: Camera.cpp Camera.h
	g++ -Wall -std=c++11 -I. -c Camera.cpp

Raytrace.o: Raytrace.cpp Raytrace.h
	g++ -Wall -std=c++11 -I. -c Raytrace.cpp

PPMPrint.o: PPMPrint.cpp PPMPrint.h
	g++ -Wall -std=c++11 -I. -c PPMPrint.cpp

Model.o: Model.cpp Model.h
	g++ -Wall -std=c++11 -I. -c Model.cpp

MatLib.o: MatLib.cpp MatLib.h
	g++ -Wall -std=c++11 -I. -c MatLib.cpp

clean:
	rm -f *.o raytracer

tar:
	tar -cvf raytracer.tar *.cpp *.h *.txt *.obj *.mtl masterwork1.ppm Makefile

over: clean all

