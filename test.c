/**

 * @file   testebbchar.c

 * @author Derek Molloy

 * @date   7 April 2015

 * @version 0.1

 * @brief  A Linux user space program that communicates with the ebbchar.c LKM. It passes a

 * string to the LKM and reads the response from the LKM. For this example to work the device

 * must be called /dev/ebbchar.

 * @see http://www.derekmolloy.ie/ for a full description and follow-up descriptions.

*/

#include<stdio.h>

#include<stdlib.h>

#include<errno.h>

#include<fcntl.h>

#include<string.h>

#include<unistd.h>



#define BUFFER_LENGTH 256               ///< The buffer length (crude but fine)

static char receive[BUFFER_LENGTH];     ///< The receive buffer from the LKM


void DumpHex(const void* , size_t );
int main(){

   int ret, fd;

   char stringToSend[BUFFER_LENGTH];

   

   printf("Starting device test code example...\n");

   fd = open("/dev/Crypto", O_RDWR);             // Open the device with read/write access

   if (fd < 0){

      perror("Failed to open the device...");

      return errno;

   }

   //printf("Type in a short string to send to the kernel module:\n");

   //scanf("%[^\n]%*c", stringToSend);                // Read in a string (with spaces)

   //printf("Writing message to the device [%s].\n", stringToSend);
   
   stpcpy(stringToSend, "d ALOBRASIL"); //d para decrypt
   ret = write(fd, stringToSend, strlen(stringToSend)); // Send the string to the LKM

   if (ret < 0){

      perror("Failed to write the message to the device.");

      return errno;

   }



   printf("Press ENTER to read back from the device...\n");

   getchar();



   printf("Reading from the device...\n");

   ret = read(fd, receive, BUFFER_LENGTH);        // Read the response from the LKM

   if (ret < 0){

      perror("Failed to read the message from the device.");

      return errno;

   }
   //printf("TEST receive : %d \n", receive);
   DumpHex(receive, 32);

   printf("End of the program\n");

   return 0;

}



void DumpHex(const void* data, size_t size) {
	char ascii[33];
	size_t i, j;
	ascii[32] = '\0';
	for (i = 0; i < size; ++i) {
		printf("%02X ", ((unsigned char*)data)[i]);
		if (((unsigned char*)data)[i] >= ' ' && ((unsigned char*)data)[i] <= '~') {
			ascii[i % 16] = ((unsigned char*)data)[i];
		} else {
			ascii[i % 16] = '.';
		}
		if ((i+1) % 8 == 0 || i+1 == size) {
			printf(" ");
			if ((i+1) % 16 == 0) {
				printf("|  %s \n", ascii);
			} else if (i+1 == size) {
				ascii[(i+1) % 16] = '\0';
				if ((i+1) % 16 <= 8) {
					printf(" ");
				}
				for (j = (i+1) % 16; j < 16; ++j) {
					printf("   ");
				}
				printf("|  %s \n", ascii);
			}
		}
	}
}

