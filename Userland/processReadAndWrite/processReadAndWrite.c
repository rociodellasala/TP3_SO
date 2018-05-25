#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <pipe.h>

int main (void){
	int pidPipe1;
	char * message;
	int pidPipe2;
	
	pidPipe1 = pipe("processWriteAndRead");
	message = malloc(20);
	read(pidPipe1,message,17);
	pidPipe2 = pipe("processWriteAndRead");
	write(pidPipe2,message,17);
	exitProcess();
	return 0;
}
