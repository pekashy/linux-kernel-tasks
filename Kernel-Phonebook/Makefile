CC=gcc
CFLAGS=-I. -static
OBJ = test.o userUtils.o
OBJ_L = test_loadable.o userUtils.o

all:

test: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

test_loadable: $(OBJ_L)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -f *.o