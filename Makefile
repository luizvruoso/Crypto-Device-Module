obj-m+=crypt_mod.o
crypt_mod-objs	:=	base.o encrypt.o decrypt.o hash.o

all:
	
	make -C /lib/modules/$(shell uname -r)/build/ M=$(shell pwd) modules
	$(CC) test.c -o test
	sudo insmod crypt_mod.ko
	sudo ./test
	sudo journalctl --since "1 minutes ago" | grep kernel
clean:
	sudo rmmod crypt_mod
	make -C /lib/modules/$(shell uname -r)/build/ M=$(shell pwd) clean
	rm test
