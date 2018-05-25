#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <pipe.h>
#include <types.h>

int main (void){
	int PID;
	char * message;
	char * message2;

	PID = pipe("processRead");
	message = "Hola llegue";
	message2 = "hola mundillo";
	
	write(PID,message,strlen(message));
	write(PID,message2,strlen(message2));
	
	while(1);
	
	exitProcess();
	return 0;
}
