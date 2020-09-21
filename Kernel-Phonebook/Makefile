CC=gcc
CFLAGS=-I. -static
OBJ = test.o userUtils.o

all:

test: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -f *.o