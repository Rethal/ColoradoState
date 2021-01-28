all: stickMan

stickMan: stick.o PoseDisplay.o multistick.o Point3D.h main.cpp
	g++ -Wall -g -std=c++11 -lX11 -I. stick.o PoseDisplay.o main.cpp -o PA4

stick.o: stick.cpp stick.h
	g++ -Wall -g -std=c++11 -lX11 -I. -c stick.cpp

PoseDisplay.o: PoseDisplay.cpp PoseDisplay.h
	g++ -Wall -g -std=c++11 -lX11 -I. -c PoseDisplay.cpp

multistick.o: multistick.cpp multistick.h
	g++ -Wall -g -std=c++11 -lX11 -I. -c multistick.cpp

clean:
	rm -f *.o PA4

tar:
	tar -cvf pa4.tar *.cpp *.h Makefile
