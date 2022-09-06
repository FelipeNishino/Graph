DIR := ${CURDIR}

exec = bin/a.out
sources = $(wildcard src/*.cpp)
objects = $(sources:.cpp=.o)
flags = -g -Wall

$(exec): $(objects)
	g++ $(objects) $(flags) -o $(exec)

%.o: %.c include/%.h
	g++ -c $(flags) $< -o $@

clean:
	-rm *.out
	-rm *.o
	-rm *.a
	-rm src/*.o

run: $(exec)
	./$(exec)

