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
    printf("enter te desired option");
    printf("0) Encrypt String ");
    printf("1) Decrypt String ");
    printf("2) Hash Resume ");
    printf("3) Group ");
    printf("4) Exit ");
}
int main(){
    int choice;
    while (choice!=4){
        do {
            menu();
            scanf("%i", &choice);
        }while(choice < 0 || choice > 4);
        system ("cls");
        

    }
}