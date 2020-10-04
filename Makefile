


#Gabriel Gonçalves Mattos Santini -  18189084
#Luiz Vinicius dos Santos Ruoso - 18233486
#Marcelo Germani Olmos -  18048298    
#Victor Felipe dos Santos -  18117820
#Victor Luiz Fraga Soldera - 18045674


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
