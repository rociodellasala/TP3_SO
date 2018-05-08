#include <stdarg.h>
#include <stdint.h>
#include <stdarg.h>
#include <stdlib.h>
#include "./include/stdio.h"
#include <types.h>
#include <string.h>

extern qword int80(qword rdi, qword rsi, qword rdx, qword rcx, qword r8, qword r9);

void clear_buffer(){
	char c;
	while(c = getchar() != EOF );
}

int main (void){
	int PID = pipe("processRead");
	close(PID,READ);
	char * message = "Hola llegue";
	char * message2 = "hola mundillo";
	int charsToRead;
	charsToRead = write(PID,message,strlen(message));
	charsToRead = write(PID,message2,strlen(message2));
	while(1);
	exitProgram();
	return 0;
}

void exitProgram(){
	int80(14,0,0,0,0,0);
}
