obj-m += testmodule.o
EXTRA_CFLAGS = -Wall -g

all:
	make -C ../linux-4.19.144 M=$(PWD) modules

clean:
	make -C ../linux-4.19.144 M=$(PWD) clean
