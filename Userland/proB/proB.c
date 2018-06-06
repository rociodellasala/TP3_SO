#include <stdlib.h>
#include <mutex.h>
#include <types.h>
#include <stdio.h>
#include <string.h>
#include <pipe.h>


int main (void){
	int fatherPID;
	int pipePID;
	char * word = "holas";

	fatherPID = getFatherPID();
	pipePID = pipe(fatherPID);

	write(pipePID,word,strlen(word));
	while(1);
	return 0;
}
