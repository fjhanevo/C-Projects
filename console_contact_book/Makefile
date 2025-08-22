# Directories
SRC_DIR = src
BUILD_DIR = build
INCLUDE_DIR = include
TARGET_DIR = bin

# Compiler
CC = gcc

# Compiler Flags
CFLAGS = -Wall -g -I$(INCLUDE_DIR)

# Find all files ending with .c in the src directory
SRCS = $(wildcard $(SRC_DIR)/*.c)

# Create a list of .o files in BUILD_DIR, corresponding to each .c source file
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)

$(info SRCS: $(SRCS))
$(info OBJS: $(OBJS))

# Executable name
TARGET = $(TARGET_DIR)/main

# Default rule
all: $(TARGET)

# Linking rule: creates final executable from obj files
$(TARGET): $(OBJS)
	@mkdir -p $(TARGET_DIR)	# only runs if target dir doesn't exist
	$(CC) $(CFLAGS) -o $@ $^

# Compilation rule: compiles each .c file into a .o object file
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(BUILD_DIR)	# only runs if target dir doesn't exist
	$(CC) $(CFLAGS) -c $< -o $@

# Clean rule: removes all generated files
clean:
	rm -rf $(BUILD_DIR)/*.o $(TARGET)

.PHONY: 
	all clean
