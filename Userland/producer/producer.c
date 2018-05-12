#include "stdlib.h"
#include "mutex.h"
#include "types.h"
#include "stdio.h"

#define PAYLOAD 20

extern qword int80(qword rdi, qword rsi, qword rdx, qword rcx, qword r8, qword r9);

int main (void){
	clear_screen();


	int payload = PAYLOAD;
	int mutexPID = mutex("ProdCons");

	printf("Cleaning mutex\n\n");
	wait(mutexPID);

	printf("Starting production with mutex PID: %d \n", mutexPID);
	while(payload != 0){
		signal(mutexPID);
		payload--;
	}

	exitProcess();
	return 0;
}
