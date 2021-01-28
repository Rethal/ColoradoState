all: stickMan

stickMan: stick.o PoseDisplay.o multistick.o Distance.o Point3D.h main.cpp
	g++ -Wall -std=c++11 -lX11 -I. stick.o PoseDisplay.o multistick.o Distance.o main.cpp -o PA10 -O2

stick.o: stick.cpp stick.h
	g++ -Wall -std=c++11 -lX11 -I. -c stick.cpp -O2

PoseDisplay.o: PoseDisplay.cpp PoseDisplay.h
	g++ -Wall -std=c++11 -lX11 -I. -c PoseDisplay.cpp -O2

Distance.o: Distance.cpp Distance.h
	g++ -Wall -std=c++11 -lX11 -I. -c Distance.cpp -O2

multistick.o: multistick.cpp multistick.h
	g++ -Wall -std=c++11 -lX11 -I. -c multistick.cpp -O2

clean:
	rm -f *.o PA10

tar:
	tar -cvf pa10.tar *.cpp *.h Makefile
