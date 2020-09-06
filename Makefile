obj-m+=crypt_mod.o
crypt_mod-objs	:=	base.o encrypt.o decrypt.o hash.o

all:
	make -C /lib/modules/$(shell uname -r)/build/ M=$(PWD) modules
	$(CC) test.c -o test
clean:
	make -C /lib/modules/$(shell uname -r)/build/ M=$(PWD) clean
	rm test
