all: p2

p2: p2.o
	g++ -Wall -g -lncurses -o p2 p2.o

p2.o: p2.cpp
	g++ -Wall -std=c++14 -g -O0 -pedantic-errors -lncurses -c p2.cpp

clean:
	rm -f p2
	rm -f p2.o 