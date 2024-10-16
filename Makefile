# Compiler and flags
CXX = gcc
CXXFLAGS = -O3 -lm  -Iinclude -Wall

SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

SOURCES = $(wildcard $(SRC_DIR)/*.c)
OBJECTS = $(SOURCES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
EXECUTABLE = $(BIN_DIR)/main

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^ 

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS)  -c $< -o $@

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

test: 
	./$(EXECUTABLE) test_data/TP1.csv 0.001 test_data/TP1_true10000.csv

.PHONY: all clean
