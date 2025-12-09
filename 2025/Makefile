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

# Create a new day directory
new:
	@DAY_NAME=$(if $(DAY),$(DAY),day$(shell date +%d)); \
	if [ -d "$$DAY_NAME" ]; then \
		echo "Error: Directory $$DAY_NAME already exists"; \
		exit 1; \
	fi; \
	mkdir $$DAY_NAME; \
	cp solution-template.cpp $$DAY_NAME/solution.cpp; \
	touch $$DAY_NAME/input.txt; \
	touch $$DAY_NAME/input-test.txt; \
	echo "Created new day directory: $$DAY_NAME"

# Usage info
help:
	@echo "Usage:"
	@echo "  make DAY=dayXX new   - Create a new day directory with template files"
	@echo "  make DAY=dayXX run   - Compile and run with input.txt"
	@echo "  make DAY=dayXX test  - Compile and run with input-test.txt"
	@echo "  make clean           - Remove all compiled files"
