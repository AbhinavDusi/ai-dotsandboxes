CC = g++
CFLAGS = -std=c++17

all: main

main:
	$(CC) -o bin/main src/main.cpp lib/*.cpp $(CFLAGS) 

clean: 
	rm bin/main

.PHONY: all clean