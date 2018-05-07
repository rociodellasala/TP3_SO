#include <stdarg.h>
#include <stdint.h>
#include <stdarg.h>
#include <stdlib.h>
#include "./include/stdio.h"
#include <types.h>

extern int int80(qword rdi, qword rsi, qword rdx, qword rcx, qword r8, qword r9);

int sleep(){
	return int80(6,0,0,0,0,0);
}


int main (void){
	clear_screen();
	int a;
	printf("Buenos dias!\n");
	printf("Deme el numero que quiera:");
	a=sleep();

	char * s;
	intToString(a,s);
	printf(s);

	/*
	char * memory = (char *) malloc(250);
	char * memory2 = (char *) malloc(300);
	char * memory3 = (char *) malloc(200);
	char * palabra = "Hola Mundo";
	
	printf("\nEl puntero reservado es:\n");
	printHexadecimal(memory);
	printf("\n");
	printf("El puntero reservado es:\n");
	printHexadecimal(memory2);
	printf("\n");
	printf("El puntero reservado es:\n");
	printHexadecimal(memory3);
	printf("\n");
	strcpy(memory,palabra);
	strcpy(memory2,"Fortnite > PUBG");
	strcpy(memory3,"Rubia aprobameee");
	printf("%s\n",memory);
	printf("%s\n",memory2);
	printf("%s\n",memory3);
	printf("Deme otro numero que quiera:");
	getNum(&a);	*/
	return 0;
}







