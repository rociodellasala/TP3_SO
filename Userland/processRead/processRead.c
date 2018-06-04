#include <stdlib.h>
#include <stdio.h>
#include <types.h>
#include <string.h>
#include <pipe.h>
#include "./include/processRead.h"

char * string1 = "Hola llegue";
char * string2 = "hola mundillo";

int main (void){
	int start = 0;

	char * firstString;
	char * secondString;

	int childPID = startProcess("processWrite");
	int pid = pipe(childPID);
	
	clear_screen();
	printStaringMessageTest();

	do{
		printf("To start the test please press 1 : ");
		getNum(&start);
	} while(start != 1);

	firstString = givenStringToStore(strlen(string1));
	whenStringIsReceived(firstString,strlen(string1),pid);
	thenFirstStringIsReceived(firstString);

	printf("\nNow we are gonna read another string to check if IPC supports multiple readings\n");

	secondString = givenStringToStore(strlen(string2));
	whenStringIsReceived(secondString,strlen(string2),pid);
	thenSecondStringIsReceived(secondString);

	start = 0;
	do{
		printf("\nTo finilize the test please press 1 : ");
		getNum(&start);
	}while(start != 1);
	clear_screen();
	exitProcess();
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

void thenFirstStringIsReceived(char * firstString){
	if(strcmp(firstString,string1)){
		printf("\nSUCCESS!!!!! --------- First string received: %s\n",firstString);
	}else{
		printf("\nERROR!!!!! --------- First string received: %s\n",firstString);
	}
}

void thenSecondStringIsReceived(char * secondString){
	if(strcmp(secondString,string2)){
		printf("\nSUCCESS!!!!! --------- Second string received: %s\n",secondString);
	}else{
		printf("\nERROR!!!!! --------- Second string received: %s\n",secondString);
	}
}

