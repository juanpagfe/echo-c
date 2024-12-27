# Compiler and flags
CC = gcc
CFLAGS = -Iinclude -Wall -Wextra

# Directories
SRC_DIR = src
BUILD_DIR = build

# Files
SRC = $(wildcard $(SRC_DIR)/*.c)
OBJ = $(SRC:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)
TARGET = $(BUILD_DIR)/echo

# Library flags
LIBS =

# Default target
all: $(TARGET)

# Link object files to create the final executable
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@

# Compile source files into object files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Debug target
debug: CFLAGS += -g
debug: $(TARGET)
	gdb $(TARGET)

# Clean build files
clean:
	rm -rf $(BUILD_DIR)

