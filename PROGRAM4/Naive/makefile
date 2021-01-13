CXX=g++
# https://richardstartin.github.io/posts/mmm-revisited
CXXFLAGS=-std=c++17 -Wall -I. -Ofast

INC_DIR = ..
SRC_DIR = .

DEPS := $(addprefix $(INC_DIR)/, common.hpp)
SRC := $(addprefix $(SRC_DIR)/, multiply.cpp)

# LIBS=-lpthread

multiply: $(SRC) $(DEPS) 
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	rm -f *.o multiply
