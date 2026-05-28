CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17

SRC = src/main.cpp
OUT = bin/core++

all:
	mkdir -p bin
	$(CXX) $(CXXFLAGS) $(SRC) -o $(OUT)

run: all
	./$(OUT)

clean:
	rm -rf bin
