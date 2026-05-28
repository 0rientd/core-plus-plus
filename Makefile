CXX = g++

CXXFLAGS = -Wall -Wextra -std=c++17 `sdl2-config --cflags`

LDFLAGS = `sdl2-config --libs`

SRC = src/main.cpp

OUT = bin/core++

all:
	$(CXX) $(CXXFLAGS) $(SRC) -o $(OUT) $(LDFLAGS)

run: all
	./$(OUT)

clean:
	rm -f $(OUT)


asdasdas

