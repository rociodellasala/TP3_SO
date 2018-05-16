#include "stdlib.h"
#include "mutex.h"
#include "types.h"
#include "stdio.h"

#define PAYLOAD 20

extern qword int80(qword rdi, qword rsi, qword rdx, qword rcx, qword r8, qword r9);

int main (void){


	int payload = PAYLOAD;
	int mutexPID = mutex("ProdCons");

	wait(mutexPID);

	while(payload != 0){
		signal(mutexPID);
		payload--;
	}

	exitProcess();
	return 0;
}
