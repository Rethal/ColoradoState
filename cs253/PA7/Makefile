all: stickMan

stickMan: stick.o PoseDisplay.o multistick.o Distance.o Point3D.h main.cpp
	g++ -Wall -g -std=c++11 -lX11 -I. stick.o PoseDisplay.o multistick.o Distance.o main.cpp -o PA7

stick.o: stick.cpp stick.h
	g++ -Wall -g -std=c++11 -lX11 -I. -c stick.cpp

PoseDisplay.o: PoseDisplay.cpp PoseDisplay.h
	g++ -Wall -g -std=c++11 -lX11 -I. -c PoseDisplay.cpp

Distance.o: Distance.cpp Distance.h
	g++ -Wall -g -std=c++11 -lX11 -I. -c Distance.cpp

multistick.o: multistick.cpp multistick.h
	g++ -Wall -g -std=c++11 -lX11 -I. -c multistick.cpp

clean:
	rm -f *.o PA7

tar:
	tar -cvf pa7.tar *.cpp *.h Makefile
