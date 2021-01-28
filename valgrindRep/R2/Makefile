all: Complex

Complex: Complex.o main.cpp
	g++ -Wall -I. Complex.o main.cpp -o complex

Complex.o: Complex.cpp Complex.h
	g++ -Wall -I. -c Complex.cpp
	
clean:
	rm -f *.o complex

tar:
	tar -cvf Complex.tar *.cpp *.h complex