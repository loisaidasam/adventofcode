# Variables
CXX = g++
CXXFLAGS = -std=c++11
TARGET = a.out
SOLUTION = solution.cpp
INPUT = input.txt
TEST_INPUT = input-test.txt

# Default target
all: run

# Target to compile the solution for a specific day
build:
	$(CXX) $(CXXFLAGS) -o $(DAY)/$(TARGET) $(DAY)/$(SOLUTION)

# Run with the main input
run: build
	./$(DAY)/$(TARGET) < $(DAY)/$(INPUT)

# Run with the test input
test: build
	./$(DAY)/$(TARGET) < $(DAY)/$(TEST_INPUT)

# Clean up
clean:
	find . -name "$(TARGET)" -exec rm -f {} +

# Usage info
help:
	@echo "Usage:"
	@echo "  make DAY=dayXX run   - Compile and run with input.txt"
	@echo "  make DAY=dayXX test  - Compile and run with input-test.txt"
	@echo "  make clean           - Remove all compiled files"
