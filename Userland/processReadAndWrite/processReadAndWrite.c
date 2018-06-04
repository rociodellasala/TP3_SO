#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <pipe.h>

int main (void){
	int pidPipe1;
	char * message;
	int pidPipe2;

	int fatherPID = getFatherPID();
	
	pidPipe1 = pipe(fatherPID);
	message = malloc(20);
	read(pidPipe1,message,17);
	pidPipe2 = pipe(fatherPID);
	write(pidPipe2,message,17);
	exitProcess();
	return 0;
}
