all: chat

chat: chat.cpp
	g++ -Wall -std=c++11 -I. chat.cpp -o chat

clean:
	rm -f *.o chat

tar:
	tar -cvf chat.tar *.cpp README.txt Makefile

