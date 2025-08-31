# Directories
SRC_DIR = src
INCLUDE_DIR = include
BUILD_DIR = build
TARGET_DIR = bin

# Compiler and flags
CC = gcc
CFLAGS = -Wall -g -I$(INCLUDE_DIR)

# Find all files ending with .c in src
SRCS = $(wildcard $(SRC_DIR)/*.c)

# Create a list of .o files in BUILD_DIR, corresponding to each .c file
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)

$(info SRCS: $(SRCS))
$(info OBJS: $(OBJS))

# Executable name
TARGET = $(TARGET_DIR)/main

# Default rule
all: $(TARGET)

# Linking rule
$(TARGET): $(OBJS)
	@mkdir -p $(TARGET_DIR)	# creates dir if it doesn't exist
	$(CC) $(CFLAGS) -o $@ $^

# Compilation rule
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean rule
clean:
	rm -rf $(BUILD_DIR)/*.o $(TARGET)

.PHONY:
	all clean

