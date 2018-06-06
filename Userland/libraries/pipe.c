#include "pipe.h"
#include "types.h"

extern qword int80(qword rdi, qword rsi, qword rdx, qword rcx, qword r8, qword r9);

int pipe(char * connectingProcessPID){
	return int80(15,(qword) connectingProcessPID,0,0,0,0);
}

int write(int pid,char * message, int messageLenght){
	int returnValue = 0;
	do{
		returnValue = int80(16,pid,(qword) message,messageLenght,0,0);
	}while(returnValue == BLOCKPROCESS);
	return returnValue;
}

int read(int pid,char * messageDestination, int charsToRead){
	int returnValue = 0;
	do{
		returnValue = int80(17,pid,(qword) messageDestination,charsToRead,0,0);
	}while(returnValue == BLOCKPROCESS);
	return returnValue;
}

void close(int pid, int operation){
	int80(18,pid,operation,0,0,0);
}

void open(int pid, int operation){
	int80(19,pid,operation,0,0,0);
}
