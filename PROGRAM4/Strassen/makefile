CXX      := g++
CXXFLAGS := -std=c++17 -Wall -I. -Ofast

INC_DIR  := ..
SRC_DIR  := .
TARGET   := strassen

DEPS     := $(addprefix $(INC_DIR)/, common.hpp)
SRC      := $(addprefix $(SRC_DIR)/, $(TARGET).cpp)


$(TARGET): $(SRC) $(DEPS) 
	$(CXX) $(CXXFLAGS) -o $@ $^
	@echo "\nSuccessful! Enter ./$(TARGET) to run.\n"

clean:
	@rm -f *.o $(TARGET)
