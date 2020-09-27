CC=gcc
OBJ_L = test_loadable.o

all:

test_loadable: $(OBJ_L)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -f *.o