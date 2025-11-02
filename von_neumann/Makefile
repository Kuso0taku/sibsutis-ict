CC=gcc
CFLAGS=-Wall -fexec-charset=UTF-8 -fextended-identifiers -finput-charset=UTF-8
LDFLAGS=
SOURCES=main.c
OBJECTS=
EXECUTABLE=$(SOURCES:.c=)


all: $(EXECUTABLE)


$(EXECUTABLE): %: %.c
	$(CC) $(CFLAGS) $@.c $(LDFLAGS) -o $@


clean:
	rm -f $(EXECUTABLE)

.PHONY: all clean
