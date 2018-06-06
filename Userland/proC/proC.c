#include <stdlib.h>
#include <mutex.h>
#include <types.h>
#include <stdio.h>
#include <pipe.h>
#include <string.h>


int main (void){
	int fatherPID;
	int pipePID;
	char * word = "adios";

	fatherPID = getFatherPID();
	pipePID = pipe(fatherPID);

	write(pipePID,word,strlen(word));
	while(1);
	return 0;
}