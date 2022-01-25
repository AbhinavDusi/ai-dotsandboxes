$(CFLAGS): -std=c++18
$(CPP): g++

all: 
	g++ -std=c++18 -o main main.cpp

clean: 
	rm main