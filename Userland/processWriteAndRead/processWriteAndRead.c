#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <pipe.h>
#include <types.h>

int main (void){
	char * messageToSend;
	char messageToReceive[30];

	int exits = 0;

	int pidPipe1, pidPipe2;
	int childPID;
	clear_screen();
	
	printf("Starting processWriteAndRead\n");
	childPID = startProcess("processReadAndWrite");
	printf("PID processWriteAndRead: %d\n\n",childPID);
	messageToSend = "Hola mundo alegre";

	printf("Writing...\n");
	pidPipe1 = pipe(childPID);
	write(pidPipe1,messageToSend,strlen(messageToSend));
	printf("Reading...\n");
	pidPipe2 = pipe(childPID);
	read(pidPipe2,messageToReceive,strlen(messageToSend));
	printf("The message read is: %s\n",messageToReceive);
	
	do{
		printf("Press 1 to exit: ");
		getNum(&exits);
	}while(exits != 1);

	clear_screen();
	exitProcess();
	return 0;
}
