#include "mutex.h"
#include "types.h"

extern qword int80(qword rdi, qword rsi, qword rdx, qword rcx, qword r8, qword r9);


int mutex(char * mutexName){
	return int80(20,(qword) mutexName,0,0,0,0);
}

void wait(int index){
	int flag;
	do{
		flag = int80(21,(qword) index,0,0,0,0);
	}while(flag == LOCK);
}

void signal(int index){
	int flag;
	do{
		flag = int80(22,(qword) index,0,0,0,0);
	}while(flag == LOCK);
}

void freeMutex(index){
	int80(23,(qword) index,0,0,0,0);
}
