#include <stdlib.h>
#include <mutex.h>
#include <types.h>
#include <stdio.h>
#include <string.h>

int main (void){
	while(1){
		putchar('a');
		printfColor(0x9AFE2E,"\nProduced! Buffer: [%s]	 Lenght: %d", getPipeBuffer(0,false,true) , strlen(getPipeBuffer(0,false,true)));
		sleep(2);
	}

	exitProcess();
	return 0;
}
