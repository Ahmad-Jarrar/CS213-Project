CXX=g++

CXXFLAGS= -Wall -I. -O3

NV_DIR = Naive
OP_DIR = Optimized
SRC_DIR = .

DEP1 := $(addprefix $(NV_DIR)/, naive.cpp)
DEP2 := $(addprefix $(OP_DIR)/, optimized.cpp)

SRC := $(addprefix $(SRC_DIR)/, main.cpp)

# LIBS=-lpthread

main: $(SRC) $(DEP1) $(DEP2)  
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	rm -f *.o main
