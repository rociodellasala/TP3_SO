#include "stdlib.h"
#include "stdio.h"
#include "mutex.h"
#include "types.h"

#define PAYLOAD 20

extern qword int80(qword rdi, qword rsi, qword rdx, qword rcx, qword r8, qword r9);

int main (void){
	clear_screen();


	int payload = PAYLOAD;
	int mutexPID = mutex("ProdCons");
	int iteration = 1;
	int flag = -1;

	printf("Starting consumer with mutex PID: %d \n", mutexPID);

	while(payload != 0){
		wait(mutexPID);
		printf("Charge %d consumed\n", iteration);
		iteration++;
		payload--;
	}


	printf("All charges consumed!!!!! \n\n");

	do{
		printf("\nPress 1 to exit:");
		getNum(&flag);
	}while(flag == -1);

	freeMutex(mutexPID);
	exitProcess();
	return 0;
}
