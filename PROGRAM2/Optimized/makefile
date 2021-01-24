CXX      := g++
CXXFLAGS := -std=c++17 -Wall -I. -O3

DEP1_DIR := ..
DEP2_DIR := .
SRC_DIR  := .
TARGET   := optimized

DEP1     := $(addprefix $(DEP1_DIR)/, common.cpp)
DEP2     := $(addprefix $(DEP2_DIR)/, subseq.cpp)
SRC      := $(addprefix $(SRC_DIR)/, $(TARGET).cpp)

$(TARGET): $(SRC) $(DEP1) $(DEP2)
	$(CXX) $(CXXFLAGS) -o $@ $^
	@echo "\nSuccessful! Enter ./$(TARGET) to run.\n"

clean:
	@rm -f *.o $(TARGET)