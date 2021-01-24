CXX      := g++
CXXFLAGS := -std=c++17 -Wall -I. -O3

DEP_DIR  := ..
SRC_DIR  := .
TARGET   := optimized

DEP      := $(addprefix $(DEP_DIR)/, common.cpp)
SRC      := $(addprefix $(SRC_DIR)/, $(TARGET).cpp)

$(TARGET): $(SRC) $(DEP)
	$(CXX) $(CXXFLAGS) -o $@ $^
	@echo "\nSuccessful! Enter ./$(TARGET) to run.\n"

clean:
	@rm -f *.o $(TARGET)
