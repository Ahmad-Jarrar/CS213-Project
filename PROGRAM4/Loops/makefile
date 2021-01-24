# https://richardstartin.github.io/posts/mmm-revisited
CXX      := g++
CXXFLAGS := -std=c++17 -Wall -I. -O3
LIBS     := -pthread

INC_DIR  := ..
SRC_DIR  := .
TARGET   := loops

DEPS     := $(addprefix $(INC_DIR)/, common.hpp)
SRC      := $(addprefix $(SRC_DIR)/, $(TARGET).cpp)


$(TARGET): $(SRC) $(DEPS) 
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LIBS)
	@echo "\nSuccessful! Enter ./$(TARGET) to run.\n"

clean:
	@rm -f *.o $(TARGET)