#include <exception.h>
#include <types.h>
#include <shell.h>
#include "./include/stdio.h"
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <testMemoryManager.h>

static void * firstPage = (void *)0x64000;
static void * secondPage = (void *)0x65000;
static void * thirdPage = (void *)0x66000;


int main() {
	clear_screen();
	int firstAmount;
	char * firstStringPointer;

	printStartTestMessage();
	printfFirstTestMessage();
	firstStringPointer = malloc(getNum(&firstAmount));
	if(assertEqualPointer(firstStringPointer,firstPage)){
		printf("\nSUCCESS!! -------- Our pointer address is: ");
		printf("0x");
		printHexadecimal(firstStringPointer);
	}else{
		printf("\nERROR!! -------- Our pointer address is: ");
		printf("0x");
		printHexadecimal(firstStringPointer);
	} 
	sleep(30);
	return 0;
}

void printStartTestMessage(){
	printf("----Welcome to the test of memory allocation in a single process----\n\n");
	printf("As this is the first program to reserve memory we know that the ''program's heap'' starts at 0x64000\n\n");
	printf("First page: 0x64000\n");
	printf("Second page: 0x65000\n");
	printf("Third page: 0x66000\n\n");
}

void printfFirstTestMessage(){
	printf("We are going to ask for some memory\n\n");
	printf("Please enter the amount of memory to ask for: ");

}


