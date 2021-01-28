all: stickMan

stickMan: stick.o PoseDisplay.o Point3D.h main.cpp
	g++ -Wall -g -std=c++11 -lX11 -I. stick.o PoseDisplay.o main.cpp -o PA2

stick.o: stick.cpp stick.h
	g++ -Wall -g -std=c++11 -lX11 -I. -c stick.cpp

PoseDisplay.o: PoseDisplay.cpp PoseDisplay.h
	g++ -Wall -g -std=c++11 -lX11 -I. -c PoseDisplay.cpp

clean:
	rm -f *.o pa2

tar:
	tar -cvf pa2.tar *.cpp *.h Makefile
