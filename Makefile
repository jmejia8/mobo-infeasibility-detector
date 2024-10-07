# Compiler and flags
CXX = g++
CXXFLAGS = -O3 -fopenmp  -Iinclude
LDFLAGS = -I/usr/include/eigen3

SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS = $(SOURCES:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)
EXECUTABLE = $(BIN_DIR)/distance_calculator

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@ $^ 

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) $(LDFLAGS)  -c $< -o $@

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

test: 
	./$(EXECUTABLE) data/A.csv

.PHONY: all clean
