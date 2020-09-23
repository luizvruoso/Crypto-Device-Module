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

#define BUFFER 258
unsigned char receber[BUFFER];


void menu(){
    printf("enter te desired option\n");
    printf("0) Encrypt String\n");
    printf("1) Decrypt String\n");
    printf("2) Hash Resume\n");
    printf("3) Group\n");
    printf("4) Exit\n");
}

void grupo(){
    printf("Gabriel Gonçalves Mattos Santini----18189084\n");
    printf("Luiz Vinicius dos Santos Ruoso------18233486\n");
    printf("Marcelo Germani Olmos---------------18048298\n");
    printf("Victor Felipe dos Santos------------18117820\n");
    printf("Victor Luiz Fraga Soldera-----------18045674\n");
    printf("press 1 to exit the program\n");
}

char HexToChar(char c){
    if (c<='9') return c-'0';
    return c - 'A' + (char)10;
}

int main(){
    int choice, file, grpVar;
    char enviar_string[BUFFER-2];
    file = open("/dev/crypto", O_RDONLY|O_WRONLY);
    int aux, aux2;
    char enviar[BUFFER];
    char escolher[] = {'c','d','h'}
    while (choice!=4){
        do {
            menu();
            scanf("%i", &choice);
        }while(choice < 0 || choice > 4);
        system ("cls");
        if(choice != 4){
            if(0 > file){
                printf("erro cod. %d, %d", file, (int)errno);
                return errno;
            }
            system("cls");
            printf("type the string that you want to send");
            if(choice == 0){
                printf("Encrypted");
            }
            if(choice == 1){
                printf("Decripted");
            }
            if(choice == 2){
                printf("Hashed");
            }
            if(choice == 3){
                grupo();
                while(1){
                    getch("%i", &grpVar);
                    if (grpVar==1){
                        return                    
                    }
                }                   
            }
            fflush(stdin);
            scanf("[^\n]%*c", enviar);
            aux = strlen(enviar);
            for(int j=0 ;j < aux; j++){
                if (enviar[j]<='z' && enviar[j]>='a') enviar[j]
                enviar[j]-=32;
            }
            int tamanho = 0;
            while (receber[tamanho] != 0) tamanho++;
            
		    unsigned char c;

		    printf("Hexadecimaç:");
		    for(int i=0;i<tamanho;i++) {
			   printf("%c", receber[i]);
            }
	
		    tamanho /= 2;
		    printf("ASCII");
		    for(int i=0;i<tamanho;i++) 	{		
			    printf(" %c", (char)(HexToChar(receber[2*i])*16 + HexToChar(receber[2*i+1])));
            }
            
	
	        for(int i=0;i<BUFFER;i++){
                 receive[i] = 0;
            }
		    getchar();
		    enviar_string[0] = 0;
		}		
        }        
    }
}