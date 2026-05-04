CC = gcc
CFLAGS = -Wall -Wextra -g
LIBS = -lSDL2

TARGET = chip8
SRCS = main.c chip8.c
OBJS = $(SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET) $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

run: $(TARGET)
	./$(TARGET) $(ROM)

.PHONY: all clean run