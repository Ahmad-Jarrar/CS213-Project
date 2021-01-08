CXX=g++
CXXFLAGS=-std=c++17 -Wall -g -I.

INC_DIR = ..
SRC_DIR = .

DEPS := $(addprefix $(INC_DIR)/, common.hpp)
SRC := $(addprefix $(SRC_DIR)/, multiply.cpp)

# LIBS=-lpthread

multiply: multiply.cpp $(DEPS) 
	$(CXX) -o $@ $^

clean:
	rm -f *.o multiply
