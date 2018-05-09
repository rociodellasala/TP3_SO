#include "types.h"
#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "testMemoryManager.h"
#include "assert.h"

extern qword int80(qword rdi, qword rsi, qword rdx, qword rcx, qword r8, qword r9);

static void * firstPage = (void *)0x67000;
static void * secondPage = (void *)0x68000;


int main() {
	int firstAmount;
	int secondAmount;
	int thirdAmount;
	int fourthAmount;
	char * firstStringPointer;
	char * secondStringPointer;
	char * thirdStringPointer;
	char * fourthStringPointer;
	
	clear_screen();

	printStartTestMessage();


	/* First test, reserve memory for first pointer of the first program of All userland */
	firstStringPointer = whenAskedForMemoryFirstPointer(&firstAmount);
	thenMemoryIsReserved(firstStringPointer);
	

	/* Second test, reserve memory for second pointer
	Check that both pointer are not equal
	Check that second pointer starts where it should */
	secondStringPointer = whenAskedForMemorySecondPointer(&secondAmount);
	thenBothPointersAreNotEqual(firstStringPointer, secondStringPointer);
	thenSecondPointerStartsWhereItShould(firstAmount,firstStringPointer,secondStringPointer);


	/*  Third test, reserve memory for third pointer
	Check that all pointers are not equal
	Check that third pointer starts at second page of user heap */
	thirdStringPointer = whenAskedForMemoryThirdPointer(&thirdAmount,firstAmount,secondAmount);
	thenAllPointersAreNotEqual(firstStringPointer, secondStringPointer, thirdStringPointer);
	thenThirdPointerStartsWhereItShould(thirdStringPointer);

	/* Fourth test, reserve memory for fourth pointer
	Check that all pointers are not equal
	Check that fourth pointer in first page */

	fourthStringPointer = whenAskedForMemoryFourthPointer(&fourthAmount,firstAmount,secondAmount);
	thenAllTestPointersAreNotEqual(firstStringPointer, secondStringPointer, thirdStringPointer, fourthStringPointer);
	thenFourthPointerStartsWhereItShould(fourthStringPointer,firstAmount,secondAmount);

	exitTest();
	clear_screen();
	clear_buffer();
	exitProgram();
	return 0;
}

void printStartTestMessage(){
	printf("----Welcome to the test of memory allocation in a single process----\n\n");
	printf("As this is the first program to reserve memory we know that the ''program's heap'' starts at 0x67000\n\n");
	printf("First page: 0x67000\n");
	printf("Second page: 0x68000\n");
	printf("Third page: 0x69000\n\n");
}

void * whenAskedForMemoryFirstPointer(int * firstAmount){
	int size;
	printfSecondTestMessage();
	getNum(&size);
	*firstAmount = size;
	return malloc((*firstAmount));
}

void printfFirstTestMessage(){
	printf("\nWe are going to ask for some memory for our first pointer\n\n");
	printf("Please enter the amount of memory to ask for: ");
}

void thenMemoryIsReserved(void * firstStringPointer){
	if(assertEqualPointer(firstStringPointer,firstPage)){
		printf("\nSUCCESS!! -------- Our pointer address is: 0x");
		printHexadecimal(firstStringPointer);
	}else{
		printf("\nERROR!! -------- Our pointer address is: 0x");
		printHexadecimal(firstStringPointer);
	} 
}

void * whenAskedForMemorySecondPointer(int * secondAmount){
	int size = 0;
	printfSecondTestMessage();
	getNum(&size);
	*secondAmount = size;
	return malloc((*secondAmount));
}

void printfSecondTestMessage(){
	printf("\n\nWe are going to ask for some memory for our second pointer\n\n");
	printf("Please enter the amount of memory to ask for: ");
}

void thenBothPointersAreNotEqual(void * firstPointer, void * secondPointer){
	if(! assertEqualPointer(firstPointer,secondPointer)){
		printf("\nSUCCESS!! -------- Pointers are not equal");
	}else{
		printf("\nERROR!! -------- Pointers are equal");
	} 
}

void thenSecondPointerStartsWhereItShould(int firstAmount, void * firstPointer, void * secondPointer){
	if(assertEqualPointer(firstPointer + firstAmount, secondPointer)){
		printf("\nSUCCESS!! -------- Second Pointer starts at: 0x");
		printHexadecimal(secondPointer);
	}else{
		printf("\nERROR!! ------- First pointer was : 0x");
		printHexadecimal(firstPointer);
		printf("The amount of memory reserved for first pointer was %d\n0x", firstAmount);
		printHexadecimal(firstPointer);
		printf(" + %d = 0x", firstAmount);
		printHexadecimal(firstPointer + firstAmount);
		printf("\nBut second pointer is: 0x");
		printHexadecimal(secondPointer);
	}
}

void * whenAskedForMemoryThirdPointer(int * thirdAmount, int firstAmount, int secondAmount){
	int size2;
	do{
		size2 = 0;
		printfThirdTestMessage(firstAmount,secondAmount);
		getNum(&size2);
	}while(size2 <= 4096 - firstAmount - secondAmount || size2 > 4096);
	*thirdAmount = size2;
	return malloc((*thirdAmount));
}

void printfThirdTestMessage(int firstAmount, int secondAmount){
	printf("\n\nWe are going to ask for some memory for our third pointer\n");
	printf("\nMemory asked should be between %d and 4096 bytes\n", 4096 - firstAmount - secondAmount);
	printf("Please enter the amount of memory to ask for: ");
}

void thenAllPointersAreNotEqual(void * firstStringPointer, void * secondStringPointer, void * thirdStringPointer){
	if(!assertEqualPointer(firstStringPointer,secondStringPointer) && !assertEqualPointer(secondStringPointer, thirdStringPointer)){
		printf("\nSUCCESS!! -------- All pointers are not equal");
	}else{
		printf("\nERROR!! -------- Some pointers are equal");
	}
}

void thenThirdPointerStartsWhereItShould(void * thirdStringPointer){
	if(assertEqualPointer(thirdStringPointer,secondPage)){
		printf("\nSUCCESS!! -------- Our pointer address is: 0x");
		printHexadecimal(thirdStringPointer);
	}else{
		printf("\nERROR!! -------- Our pointer address is: 0x");
		printHexadecimal(thirdStringPointer);
	} 
}

void * whenAskedForMemoryFourthPointer(int * fourthAmount, int firstAmount, int secondAmount){
	int size;
	do{
		size = 0;
		printfFourthTestMessage(firstAmount,secondAmount);
		getNum(&size);
	}while(size < 0 || size > 4096 - firstAmount - secondAmount);
	*fourthAmount = size;
	return malloc((*fourthAmount));
}

void printfFourthTestMessage(int firstAmount, int secondAmount){
	printf("\n\nWe are going to ask for some memory for our fourth pointer\n");
	printf("\nMemory asked should be between 0 and %d bytes\n", 4096 - firstAmount - secondAmount);
	printf("Please enter the amount of memory to ask for: ");
}

void thenAllTestPointersAreNotEqual(void * firstStringPointer, void * secondStringPointer, void * thirdStringPointer, void * fourthStringPointer){
	if(!assertEqualPointer(firstStringPointer,secondStringPointer) && !assertEqualPointer(secondStringPointer, thirdStringPointer)
		&& !assertEqualPointer(thirdStringPointer,fourthStringPointer)){
		printf("\nSUCCESS!! -------- All pointers are not equal");
	}else{
		printf("\nERROR!! -------- Some pointers are equal");
	}
}

void thenFourthPointerStartsWhereItShould(void * fourthStringPointer, int firstAmount, int secondAmount){
	if(assertEqualPointer(fourthStringPointer,firstPage + firstAmount + secondAmount)){
		printf("\nSUCCESS!! -------- Our pointer address is: 0x");
		printHexadecimal(fourthStringPointer);
	}else{
		printf("\nERROR!! -------- Our pointer address is: 0x");
		printHexadecimal(fourthStringPointer);
	} 
}

void exitTest(){
	int buttonPressed;
	printf("\n\nTo exit test press 0");
	do{
		printf("\nButton pressed: ");
		getNum(&buttonPressed);
	}while(buttonPressed != 0);
}

void exitProgram(){
	int80(14,0,0,0,0,0);
}

