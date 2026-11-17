# ==============================================================================
# Project: SIGNAL LAB
# File: Makefile
# Description: Build automation and memory profiling rules for SIGNAL-LAB
# Author: Ibrahim
# Date: November 2026
# ==============================================================================

CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -O3 -g -Iinclude
LDFLAGS = -lm

# Directories
SRC_DIR = src
INC_DIR = include
BIN_DIR = bin

# Target executable name
TARGET = $(BIN_DIR)/signal_lab

# Source and Object files
SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c, $(BIN_DIR)/%.o, $(SRCS))

# Default rule
all: directories $(TARGET)

# Create necessary directories
directories:
	@mkdir -p $(BIN_DIR)
	@mkdir -p data

# Compile target executable
$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $@ $(LDFLAGS)
	@echo "Build successful: $(TARGET)"

# Compile source files into object files inside bin/
$(BIN_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean build artifacts
clean:
	rm -rf $(BIN_DIR)/*
	@echo "Cleaned all binary and object files."

# Memory leak check with Valgrind (Requirement F1)
valgrind: all
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes $(TARGET)

.PHONY: all directories clean valgrind