#include "types.h"
#include "stdio.h"
#include "string.h"
#include "stdlib.h"

int main (void){
	clear_screen();
	char * messageToSend = "Hola mundo alegre";
	char * messageToReceive = malloc(strlen(messageToSend) + 1);
	int exits = 0;
	int pidPipe1 = pipe("processReadAndWrite");
	write(pidPipe1,messageToSend,strlen(messageToSend));
	int pidPipe2 = pipe("processReadAndWrite");
	read(pidPipe2,messageToReceive,strlen(messageToSend));
	printf("El mensaje que llego es: %s\n",messageToReceive);
	do{
		printf("Press 1 to exit: ");
		getNum(&exits);
	}while(exits != 1);
	exitProcess();
	return 0;
}
