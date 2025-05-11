# Compiler and flags
CXX = g++
CXXFLAGS = -O3 -march=native -Iinclude
OMPFLAGS = -fopenmp

# Source files
SRC = $(shell find src -type f -name "*.cpp")

# Object files
OBJ = $(SRC:.cpp=.o)

# Output executable name
TARGET = RailVision

# Default rule to build the program
$(TARGET): $(OBJ)
	$(CXX) $(OBJ) -o $(TARGET) $(OMPFLAGS)

# Rule to compile each .cpp file into a .o file
%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(OMPFLAGS) -c $< -o $@

# Clean rule to remove generated files
clean:
	rm -f $(OBJ) $(TARGET)