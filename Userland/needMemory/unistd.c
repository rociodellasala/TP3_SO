#include <unistd.h>
#include <stdio.h>
#include <types.h>

extern void int80(qword rdi, qword rsi, qword rdx, qword rcx, qword r8, qword r9);

void sleep(){
	long time = 600000000;
	int80(6, time, 0, 0, 0, 0);
	nextLine();	
	printf("Waking up...");
}


