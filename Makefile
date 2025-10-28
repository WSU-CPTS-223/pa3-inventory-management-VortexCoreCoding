out: clean compile execute

compile: main.cpp item.o
	g++ -g -Wall -std=c++11 main.cpp item.o -g -o PA3

item.o:
	g++ -std=c++11 -Wfatal-errors item.cpp -g -o item.o -c

execute: PA3
	./PA3

clean:
	rm -f *.o
	rm -f PA3