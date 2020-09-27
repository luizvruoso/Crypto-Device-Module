/*
   Gabriel Gonçalves Mattos Santini -  18189084
	Luiz Vinicius dos Santos Ruoso - 18233486
   Marcelo Germani Olmos -  18048298    
   Victor Felipe dos Santos -  18117820
   Victor Luiz Fraga Soldera - 18045674
*/


#include <stdio.h>

#include <stdlib.h>

#include <errno.h>

#include <fcntl.h>

#include <string.h>

#include <unistd.h>


#define clear() printf("\033[H\033[J")


#define BUFFER_LENGTH 256               ///< The buffer length (crude but fine)

static char receive[BUFFER_LENGTH];     ///< The receive buffer from the LKM

void menu();
void callEncriptacao(int);
void callDecriptcao(int);
void callHashResume(int);
void lerString(char*);
void DumpHex(const void* , size_t );
void writeToModule(int, char*);
void readFromModule(int, int);

int main(){

   int ret, fd;
   int ctrlWhileOp=0;
   char stringToSend[BUFFER_LENGTH];
   char opUsuario;
   
   // Open the device with read/write access
   printf("Starting device test code example...\n");

   fd = open("/dev/Crypto", O_RDWR);             

   if (fd < 0){

      perror("Failed to open the device...");

      return errno;

   }

   // FIM


   
   menu();
   do{
      opUsuario = getchar();
      switch(opUsuario){
         
         case 'c':
            callEncriptacao(fd);
            ctrlWhileOp = 1;
         break;
         case 'd':
            callDecriptcao(fd);
            ctrlWhileOp = 1;
         break;
         case 'h':
            callHashResume(fd);
            ctrlWhileOp = 1;
         break;
         case 'e':
            printf("\n PROGRAMA FINALIZADO! \n");
            ctrlWhileOp = 0;
         break;

         default: 
            clear();
            printf("\n Digite uma opção valida \n");
            menu();
            
            ctrlWhileOp = 1;
         break;
      
      }
      

   }while(ctrlWhileOp);

  
   return 0;

}



void DumpHex(const void* data, size_t size) {
	char ascii[45];
	size_t i, j;
	ascii[45] = '\0';
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

void lerString(char *aux){
   getchar();
   printf("Digite sua String: \n");
   fgets(aux, 33, stdin);
    
}

void writeToModule(int fd, char *stringToSend){
   int ret;

   ret = write(fd, stringToSend, strlen(stringToSend)); // Send the string to the LKM

   if (ret < 0){

      perror("Failed to write the message to the device.");

      return errno;

   }
}

void readFromModule(int fd, int size){
   int ret;

   printf("Reading from the device...\n");

   ret = read(fd, receive, BUFFER_LENGTH);        // Read the response from the LKM

   if (ret < 0){

      perror("Failed to read the message from the device.");

      return errno;

   }
   //printf("TEST receive : %d \n", receive);
   DumpHex(receive, size);

   //printf("End of the program\n");
}

void callEncriptacao(int fd){

   char aux[33]={0};
   char stringToSend[35];
   int ret;
   lerString(aux);
   
   //printf("\n conteudo string %s", aux);
   stringToSend[0] = 'c';
   stringToSend[1] = ' ';
   strcpy(stringToSend+2, aux);

   
   writeToModule(fd, stringToSend);
   readFromModule(fd, 16);

   printf("Pressione uma tecla para continuar");
   getchar();
   return;
}

void callDecriptcao(int fd){
   char aux[33]={0};
   char stringToSend[35];
   int ret;
   lerString(aux);
   
  
   stringToSend[0] = 'd';
   stringToSend[1] = ' ';
   strcpy(stringToSend+2, aux);

   
   writeToModule(fd, stringToSend);
   readFromModule(fd, 16);

   printf("Pressione uma tecla para continuar");
   getchar();
   return;

}

void callHashResume(int fd){
   char aux[41]={0};
   char stringToSend[45];
   int ret;
   lerString(aux);
   
  
   stringToSend[0] = 'h';
   stringToSend[1] = ' ';
   strcpy(stringToSend+2, aux);

   
   writeToModule(fd, stringToSend);
   readFromModule(fd, 20);

   printf("Pressione uma tecla para continuar");
   getchar();
   return;
}

void menu(){
    printf("Escolha uma Opção \n");
    printf(" c ) Encrypt String \n");
    printf(" d ) Decrypt String \n");
    printf(" h ) Hash Resume \n");
    printf(" e ) Exit\n");
}

