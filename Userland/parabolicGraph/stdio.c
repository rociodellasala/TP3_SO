#include "string.h"
#include "stdarg.h"
#include "types.h"
#include "stdlib.h"
#include "stdio.h"

extern qword int80(qword rdi, qword rsi, qword rdx, qword rcx, qword r8, qword r9);

void putchar(unsigned char c) {
	int80(1, c, 1, 0, 0, 0);
}

void backspace() {
	char c = '\b';
	int80(1, 0 ,(qword) &c, 1 ,0, 0);
}

void printf(const char * str,...){
	char num[12];
	va_list arguments;
	va_start(arguments, str);
	int length = strlen(str);
	int state = 0;

	for(int x = 0; x < length; x++){
		if(state == 0){
			if(str[x] != '%')
				putchar(str[x]);
			else
				state = 1;
		}else{
			switch(str[x]){
				case 'd':
					intToString(va_arg(arguments, int), num);
					int index = 0;
					while(num[index] != 0)
						putchar(num[index++]);
					state = 0;
					break;
				case 'c':
					putchar((char)(va_arg(arguments, int)));
					state = 0;
					break;
				case 's':
					printf(va_arg(arguments, char *));
					state = 0;
					break;
				default:	
					putchar('%');
					putchar(str[x]);
					state = 0;
					break;
			}
		}
	}

	va_end(arguments);
}

void clear_screen(){
	int80(2, 1, 0, 0, 0, 0);
}

void draw_pixel(int x, int y){
	int80(8, x, y, 0, 0, 0);
}

char getchar(){
	unsigned char c[2];
	int80(3, 0, (qword) c, 2, 0, 0);

	if(c[0] == 0 ){
		return EOF;
	}

	return c[0];
}

int strlen(const char * str) {
  int length = 0;

  while(*str != '\0') {
    str++;
    length++;
  }

  return length;
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
