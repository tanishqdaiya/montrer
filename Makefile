CC      := gcc
CFLAGS  := -Wall -Wextra -O2 -std=c17
TARGET  := montrer
SRCS    := montrer.c
OBJS    := $(SRCS:.c=.o)

.PHONY: all clean montrer

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJS) $(TARGET) $(wildcard *.html)
