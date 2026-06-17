CC = gcc
CFLAGS = -Wall -Wextra -O2
LIBS = -lm
TARGET = teste_intersec
SRC = elementos_de_cg.c main.c
OBJ = $(SRC:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ) $(LIBS)

%.o: %.c elementos_de_cg.h
	$(CC) $(CFLAGS) -c $< -o $@

run: all
	./$(TARGET)

clean:
	rm -f $(OBJ) $(TARGET)

.PHONY: all run clean
