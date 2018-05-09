#include "stdlib.h"
#include "stdio.h"
#include "types.h"

extern void int80(qword rdi, qword rsi, qword rdx, qword rcx, qword r8, qword r9);

void intToString(int num, char * str){
	int dig = 0;
	char aux;

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
		for(int x = 0; x < dig / 2; x++){
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

void printMsg(int j){
	while(j < 50000000){
		j++;	
	}
	printf("\nSolo si corro en foreground podras leer mi mensaje!");
}

void clear_buffer(){
	char c;
	while((c = getchar()) != EOF );
}

void printHexadecimal(void * pointer){
	int80(11,(qword) pointer,0,0,0,0);
}
