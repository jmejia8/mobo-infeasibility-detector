# Compiler and flags
CXX = gcc
CXXFLAGS = -O3 -lm -Iinclude -Wall -fPIC
LDFLAGS = -shared

SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

SOURCES = $(wildcard $(SRC_DIR)/*.c)
OBJECTS = $(SOURCES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
EXECUTABLE = $(BIN_DIR)/detector
SHARED_LIB = $(BIN_DIR)/libdetector.so  # Name of the shared library

all: $(EXECUTABLE) $(SHARED_LIB)

# Rule for creating the executable
$(EXECUTABLE): $(OBJECTS)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Rule for creating the shared library
$(SHARED_LIB): $(OBJECTS)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@ $^

# Compile object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

test: $(EXECUTABLE)
	./$(EXECUTABLE) test_data/TP1.csv 0.001 test_data/TP1_true10000.csv

.PHONY: all clean
