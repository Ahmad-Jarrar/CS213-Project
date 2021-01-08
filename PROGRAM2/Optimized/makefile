CXX=g++
# https://richardstartin.github.io/posts/mmm-revisited
CXXFLAGS=-std=c++17 -Wall -I. -Ofast

INC_DIR = ..
SRC_DIR = .

# DEPS := $(addprefix $(INC_DIR)/, common.hpp)
SRC := $(addprefix $(SRC_DIR)/, prog2_optimized.cpp)

# LIBS=-lpthread

prog2_optimized: $(SRC)
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	rm -f *.o prog2_optimized
