#include <types.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>

extern void int80(qword rdi, qword rsi, qword rdx, qword rcx, qword r8, qword r9);

void printf(const char * str, ...){
	char num[12];
	va_list arguments;
	va_start (arguments, str);
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
					while(num[index] != 0){
						putchar(num[index++]);
					}
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

void putchar(unsigned char c) {
	int80(1, c, 1, 0, 0, 0);
}

char getchar() {
	unsigned char c[2];
	int80(3, 0, c, 2, 0, 0);
	if(c[0] == 0 ) 
		return EOF;
	return c[0];
}

void backspace() {
	int80(7, 0, 0, 0 ,0, 0);
}

void clear_screen(){
	int80(2, 1, 0, 0, 0, 0);
}

void clear_terminal() {
	int80(2, 1, 0, 0, 0, 0);
	printf("$>:  ");
}

void nextLine(){
	int80(5, 0, 0, 0, 0, 0);
}

void nextTerminalLine(){
	int80(5, 0, 0, 0, 0, 0);
	printf("$>:  ");
}

int changeFontColor(char * color){
	if(strcmp(color, "blue")) {
		int80(4, 0x0000FF, 0, 0, 0, 0);
	} else if(strcmp(color, "red")){
		int80(4, 0xFF0000, 0, 0, 0, 0);
	} else if(strcmp(color, "violet")){
		int80(4, 0x9900FF, 0, 0, 0, 0);
	} else if(strcmp(color, "white")){
		int80(4, 0xFFFFFF, 0, 0, 0, 0);
	} else if(strcmp(color, "yellow")){
		int80(4, 0xFFFF00, 0, 0, 0, 0);
	} else {
		return 1;
	}
	return 0;
}

void time(){
	int80(9, 0, 0, 0, 0, 0);
	return;
}






