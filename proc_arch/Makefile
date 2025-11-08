CC=gcc
CFLAGS=-Wall -fexec-charset=UTF-8 -fextended-identifiers -finput-charset=UTF-8
LDFLAGS=-lm
SOURCES=main.c
OBJECTS=
EXECUTABLE=$(SOURCES:.c=)

all: $(EXECUTABLE)

$(EXECUTABLE): %: %.c
	$(CC) $(CFLAGS) $@.c $(LDFLAGS) -o $@
	find_cpu_model.sh

clean:
	rm -f $(EXECUTABLE)
	rm -f cpu_model

.PHONY: all clean
