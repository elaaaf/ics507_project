# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -Wextra -g #enable compiler warnings + debug mode

# Files
SRCS = $(wildcard *.c) $(wildcard src/*.c) $(wildcard src/utils/*.c)
OBJS = $(SRCS:.c=.o)

# Include headers
INCLUDES = -I include

# Output file
TARGET = mxm

# Default rule
all: $(TARGET)

# Link the object files to create the executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Compile each .c file into .o
%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Clean up build files
clean:
	rm -f $(OBJS) $(TARGET) *.txt

# Phony targets (not files)
.PHONY: all clean
