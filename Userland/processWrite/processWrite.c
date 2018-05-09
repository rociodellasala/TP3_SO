#include "types.h"
#include "stdio.h"
#include "string.h"
#include "stdlib.h"

extern qword int80(qword rdi, qword rsi, qword rdx, qword rcx, qword r8, qword r9);

int main (void){
	clear_screen();
	int PID = pipe("processRead");
	char * message = "Hola llegue";
	char * message2 = "hola mundillo";
	write(PID,message,strlen(message));
	write(PID,message2,strlen(message2));
	while(1);
	exitProcess();
	return 0;
}
