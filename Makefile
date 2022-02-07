CLFAGS = -std=c++17
CPP = g++

all: 
	$(CPP) $(CFLAGS) -o main main.cpp

clean: 
	rm main