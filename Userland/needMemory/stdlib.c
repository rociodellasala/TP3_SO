#include <stdlib.h>
#include <types.h>

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

/*
void * malloc(int size){
	return int80(10,size,0,0,0,0);
}*/

void printHexadecimal(void * pointer){
	int80(11,pointer,0,0,0,0);
}
