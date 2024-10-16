CC=gcc
CFLAGS=-O2 -march=armv8-a+sve -std=c11
INCLUDES=-Iinclude

TARGET=main

# List all your .c files here
SRC=src/main.c src/utils.c src/mat_utils.c src/tests.c

# Automatically generate object file names from the source file names.
OBJ=$(SRC:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES)

clean:
	rm -f $(TARGET) $(OBJ)

.PHONY: all clean