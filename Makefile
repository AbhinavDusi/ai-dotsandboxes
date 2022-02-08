CC = g++
CFLAGS = -std=c++17

all: main

main:
	$(CC) -o main main.cpp $(CFLAGS) 

clean: 
	rm main