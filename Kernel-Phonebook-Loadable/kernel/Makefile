obj-m += addressbook.o 

all:
	make -C ../linux-4.19.144 M=$(PWD) modules

clean:
	make -C ../linux-4.19.144 M=$(PWD) clean
