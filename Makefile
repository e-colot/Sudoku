# Directories
BUILD_DIR := ./build
SRC_DIRS := ./src

# Find all the C files we want to compile
SRCS := $(shell find $(SRC_DIRS) -name '*.c')

# Convert source files to object files in the build directory, preserving the directory structure
OBJS := $(SRCS:$(SRC_DIRS)/%.c=$(BUILD_DIR)/%.o)

# Compiler and flags
CC := gcc
CFLAGS := -Wall -Werror -Iinclude $(shell sdl2-config --cflags)
LDFLAGS := $(shell sdl2-config --libs)

# Target executable
TARGET := sudoku

# Rule to build the target executable
$(TARGET): $(OBJS)  # needs the rule under to be executed before to have .o files
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

# Rule to build object files
$(BUILD_DIR)/%.o: $(SRC_DIRS)/%.c
	@mkdir -p $(dir $@)   # Create the build directory if it doesn't exist
	$(CC) $(CFLAGS) -c -o $@ $<
		# $@ refers to the obj file (see as a for loop where @ is the iterator trough the files)
		# $< refers to the first prerequisit (here the .C files needed to build the .o files)
		# $^refers to the other prerequisities that might be needed

# Clean rule
.PHONY: clean
clean:
	rm -rf $(BUILD_DIR) $(TARGET)
