all: main.o
	g++ main.cc -o main -lsfml-system -lsfml-graphics -lsfml-window -lsfml-audio
main.o: main.cc
	g++ -c main.cc
clean:
	rm -rf *.o
