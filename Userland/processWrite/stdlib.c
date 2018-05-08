#include <stdlib.h>
#include <stdio.h>
#include <types.h>

extern qword int80(qword rdi, qword rsi, qword rdx, qword rcx, qword r8, qword r9);

void intToString(int num, char * str){
	int dig = 0;
	char aux;

	if(num != 0){
		/*If number is negative then the first character is '-' */
		if(num < 0){
			num = -num;
			str[0] = '-';
			dig++;
		}

		/* Calculate character */
		while(num != 0){
			str[dig] = (num % 10) + '0';
			num = num / 10;
			dig++;
		}

		/* Reverse array */
		for(int x = 0; x < dig / 2; x++){
			aux = str[x];
			str[x] = str[dig - x - 1];
			str[dig - x - 1] = aux;
		}

		/* Terminate array */
		str[dig] = 0;
	}else{
		str[0] = '0';
	}	
}

void * malloc(int size){
	return int80(10,size,0,0,0,0);
}

void printHexadecimal(void * pointer){
	int80(11,pointer,0,0,0,0);
}

int getPID(){
	return int80(20,0,0,0,0,0);
}

int pipe(char * connectingProcessName){
	int80(15,connectingProcessName,0,0,0,0);
	return getPID();
}

int write(int pid,char * message, int messageLenght){
	return int80(16,pid,message,messageLenght,0,0);
}

int read(int pid,char * messageDestination, int charsToRead){
	return int80(17,pid,messageDestination,charsToRead,0,0);
}

void close(int pid, int operation){
	int80(18,pid,operation,0,0,0);
}

void open(int pid, int operation){
	int80(19,pid,operation,0,0,0);
}