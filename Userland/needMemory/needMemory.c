#include <stdarg.h>
#include <stdint.h>
#include <stdarg.h>
#include <stdlib.h>
#include "./include/stdio.h"

static void * somewhere = (void *)0x64000;
static void * another = (void *)0x64020;

int main (void){
	clear_screen();
	int a;
	int b;
	printf("Bueno dias!\n");
	printf("Deme el numero que quiera:");
	getNum(&a);
	char * memory = (char *) malloc(301);
	char * memory2 = (char *) malloc(600);
	char * memory3 = (char *) malloc(100);
	printf("\nEl puntero reservado es:\n");
	printHexadecimal(memory);
	printf("\n");
	printf("El puntero reservado es:\n");
	printHexadecimal(memory2);
	printf("\n");
	printf("El puntero reservado es:\n");
	printHexadecimal(memory3);
	printf("\n");
	printf("%d\n",b);
	printf("\n");
	printf("Deme otro numero que quiera:");
	if(somewhere == memory)
		printf("jaja");
	else if(another == memory)
		printf("jeje");
	getNum(&a);
	return 0;
}










