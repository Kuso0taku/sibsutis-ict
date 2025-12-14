CC=gcc
CFLAGS=-Wall -Wextra -fexec-charset=UTF-8 -fextended-identifiers -std=c11 -O2
LDFLAGS=
SOURCES=strfunc.c conpyc.c main.c
OBJECTS=$(SOURCES:.c=.o)
HEADERS=strfunc.h conpy.h consts.h
TARGET=program

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@

%.o: %.c 
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) $(OBJECTS)

.PHONY: all clean
