CC=gcc
CFLAGS=-I. -static
DEPS = inc/user.h
OBJ = test.o

all:

test: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -f *.o