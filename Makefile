.PHONY: clean

CC = gcc

CFLAGS = -I include 
CFILES = $(shell find src -name "*.c")
OBJS = $(CFILES:.c=.o)
TARGET = g--

RM = -rm -f

all: $(TARGET)


$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)

%o : %c
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	$(RM) $(TARGET) $(OBJS)

debug:
	 gcc -I include -g $(CFILES) -o ./testfile