#include "converter.h"
#include "video_driver.h"

static char buffer[64] = { '0' };

void printDec(qword value){
	printBase(value, 10);
}

void printHex(qword value){
	printBase(value, 16);
}

void printBin(qword value){
	printBase(value, 2);
}

void printBase(qword value, dword base){
    	uintToBase(value, buffer, base);
   	print_string(buffer);
}

dword uintToBase(qword value, char * buffer, dword base){
	char *p = buffer;
	char *p1, *p2;
	dword digits = 0;

	do{
		dword remainder = value % base;
		*p++ = (remainder < 10) ? remainder + '0' : remainder + 'A' - 10;
		digits++;
	} while (value /= base);

	*p = 0;

	p1 = buffer;
	p2 = p - 1;
	
	while (p1 < p2){
		char tmp = *p1;
		*p1 = *p2;
		*p2 = tmp;
		p1++;
		p2--;
	}

	return digits;
}

void intToString(int num, char * str){
	int dig = 0;
	char aux;
	
	if(num != 0){
		if(num < 0){
			num = -num;
			str[0] = '-';
			dig++;
		}

		while(num != 0){
			str[dig] = (num % 10) + '0';
			num = num / 10;
			dig++;
		}
	
		for(int x = 0; x < dig / 2; x++){
			aux = str[x];
			str[x] = str[dig - x - 1];
			str[dig - x - 1] = aux;
		}

		str[dig] = 0;
	} else {
		str[0] = '0';
	}	
}
