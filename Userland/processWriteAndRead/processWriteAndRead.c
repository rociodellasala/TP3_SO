#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <pipe.h>
#include <types.h>

int main (void){
	char * messageToSend;
	char * messageToReceive;

	int exits = 0;

	int pidPipe1, pidPipe2;
	int childPID;
	clear_screen();
	
	printf("Comenzando processWriteAndRead\n");
	childPID = startProcess("processReadAndWrite");
	printf("PID processWriteAndRead: %d\n\n",childPID);
	messageToSend = "Hola mundo alegre";
	messageToReceive = malloc(strlen(messageToSend) + 1);

	printf("Escribiendo...\n");
	pidPipe1 = pipe(childPID);
	write(pidPipe1,messageToSend,strlen(messageToSend));
	printf("Leyendo...\n");
	pidPipe2 = pipe(childPID);
	read(pidPipe2,messageToReceive,strlen(messageToSend));
	printf("El mensaje que llego es: %s\n",messageToReceive);
	
	do{
		printf("Press 1 to exit: ");
		getNum(&exits);
	}while(exits != 1);

	clear_screen();
	exitProcess();
	return 0;
}
