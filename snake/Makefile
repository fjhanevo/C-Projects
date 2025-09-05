# Directories
SRC_DIR = src
BUILD_DIR = build
INCLUDE_DIR = include
TARGET_DIR = bin

# Compiler
CC = gcc
# compiler flags
CFLAGS = -Wall -g -I$(INCLUDE_DIR)
#linker libraries
LDLIBS = -lncurses


SRCS = $(wildcard $(SRC_DIR)/*.c)

OBJS = $(SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)

$(info SRCS: $(SRCS))
$(info OBJS: $(OBJS))

TARGET = $(TARGET_DIR)/main

# default rule
all: $(TARGET)

# linking
$(TARGET): $(OBJS)
	@mkdir -p $(TARGET_DIR) 	# create dir if it doesn't exist
	$(CC) $(CFLAGS) -o $@ $^ $(LDLIBS)

# compilation
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean: 
	rm -rf $(BUILD_DIR) $(TARGET_DIR)

.PHONY: 
	all clean
