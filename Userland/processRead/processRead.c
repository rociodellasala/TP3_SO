#include <stdarg.h>
#include <stdint.h>
#include <stdarg.h>
#include <stdlib.h>
#include "./include/stdio.h"
#include <types.h>
#include <string.h>
#include <processRead.h>

extern qword int80(qword rdi, qword rsi, qword rdx, qword rcx, qword r8, qword r9);

char const * string1 = "Hola llegue";
char const * string2 = "hola mundillo";

void clear_buffer(){
	char c;
	while(c = getchar() != EOF );
}

int main (void){
	int start = 0;
	int pid = getPID();
	pipe("processWrite");
	char * firstString;
	char * secondString;
	clear_screen();
	printStaringMessageTest();

	do{
		printf("To start the test please press 1 : ");
		getNum(&start);
	}while(start != 1);

	firstString = givenStringToStore(strlen(string1));
	whenStringIsReceived(firstString,strlen(string1),pid);
	thenFirstStringIsReceived(firstString);

	printf("Know we are gonna read another string to check if IPC supports multiple readings\n");

	secondString = givenStringToStore(strlen(string2));
	whenStringIsReceived(secondString,strlen(string2),pid);
	thenSecondStringIsReceived(secondString);

	start = 0;
	do{
		printf("To finilize the test please press 1 :");
		getNum(&start);
	}while(start != 1);
	clear_screen();
	exitProgram();
	return 0;
}

void printStaringMessageTest(){
	printf("			---------------IPC TEST---------------\n\n");
	printf("The test consists in read 2 times from a pipe\n");
	printf("The test will succed only if both strings are the expected ones\n\n");
}

char * givenStringToStore(int size){
	return malloc(size);
}

void whenStringIsReceived(char * firstString, int charsToRead, int pid){
	read(pid,firstString,charsToRead);
}

void thenFirstStringIsReceived(char const * firstString){
	if(strcmp(firstString,string1)){
		printf("SUCCESS!!!!! --------- First string received: %s\n",firstString);
	}else{
		printf("ERROR!!!!! --------- First string received: %s\n",firstString);
	}
}

void thenSecondStringIsReceived(char const * secondString){
	if(strcmp(secondString,string2)){
		printf("SUCCESS!!!!! --------- Second string received: %s\n",secondString);
	}else{
		printf("ERROR!!!!! --------- Second string received: %s\n",secondString);
	}
}

void exitProgram(){
	int80(14,0,0,0,0,0);
}


