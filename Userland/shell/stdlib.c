#include "types.h"
#include "shell.h"
#include "stdio.h"

extern qword int80(qword rdi, qword rsi, qword rdx, qword rcx, qword r8, qword r9);

void intToString(int num, char * str){
	int dig = 0;
	char aux;
	int x;

	if(num != 0){
		/*If number is negative then the first character is '-' */
		if(num < 0){
			num = -num;
			str[0] = '-';
			dig++;
		}

		/* Calculate character */
		while(num != 0){
			str[dig] = (num % 10) + '0';
			num = num / 10;
			dig++;
		}

		/* Reverse array */
		for(x = 0; x < dig / 2; x++){
			aux = str[x];
			str[x] = str[dig - x - 1];
			str[dig - x - 1] = aux;
		}

		/* Terminate array */
		str[dig] = 0;
	}else{
		str[0] = '0';
	}	
}

void exitProcess(){
	int80(14,0,0,0,0,0);
}

int startProcess(char * program){
	int i = int80(12, (qword) program,0,0,0,0);
	if(i == -1)
		return 1;
	return 3;
}

void ps(){
	nextLine();	
	int80(13, 0, 0, 0, 0, 0);
}

void ls(){
	nextLine();	
	nextLine();	
	printf("      linearGraph      parabolicGraph      testMemoryManager      processReadAndWrite");
	nextLine();
	nextLine();
	printf("      processRead      processWrite           background          processWriteAndRead");
	nextLine();
	nextLine();
	printf("      producer         consumer");
	nextLine();
}

void time(){
	int80(9, 0, 0, 0, 0, 0);
	return;
}
