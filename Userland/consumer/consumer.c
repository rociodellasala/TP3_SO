#include <stdlib.h>
#include <mutex.h>
#include <types.h>
#include <stdio.h>
#include <string.h>

int main (void){
	while(1){
		getchar();
		printfColor(0xFE2E2E,"\nConsumed! Buffer: [%s]	 Lenght: %d", getPipeBuffer(0,true,false) , strlen(getPipeBuffer(0,true,false)));
		sleep(2);
	}

	exitProcess();
	return 0;
}
