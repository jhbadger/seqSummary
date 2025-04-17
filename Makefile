# Makefile for seqSummary

# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -O2  # -Wall enables all warnings, -g for debugging, -O2 for optimization

# Source files
SRC = seqSummary.c loadfasta.c utils.c

# Executable name
TARGET = seqSummary

# Object file name
OBJ = $(TARGET).o loadfasta.o utils.o

# Default rule: builds the executable
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

# Create the object file from the C source file
$(OBJ): $(SRC) 
	$(CC) $(CFLAGS) -c $(SRC)

# Clean rule: removes the executable and object file
clean:
	rm -f $(TARGET) $(OBJ)

# Phony targets (targets that don't represent files)
.PHONY: clean