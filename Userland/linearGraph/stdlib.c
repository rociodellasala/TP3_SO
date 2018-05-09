#include "stdlib.h"
#include "types.h"
#include "stdio.h"

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

void clear_buffer(){
	char c;
	while((c = getchar()) != EOF );
}

void exitProcess(){
	int80(14,0,0,0,0,0);
}

char * readInt(char * string, int * num){
    *num = 0;
	boolean sign = 1;

    if(*string == '-'){
		if (isNum(*(string + 1))){
			sign = -1;
			*num = (*(string + 1) - '0') * sign;
			string++;
			string++;
		}else{
			return string;
		}
	}

	int c;

    while (isNum(c = *string)){
        *num = (*num) * 10 + (c - '0') * sign;
        string++;
    }

    return string;
}

int isNum(char c){
	return (c >= '0' && c <= '9');
}

