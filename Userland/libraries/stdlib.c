#include "stdlib.h"
#include "types.h"
#include "string.h"
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

int stringToInt(char * str){
	int strLen = strlen(str);
	int mult = (strLen - 1) * 10;
	int returnInt = 0;
	int i = 1;
	char digit;

	if(strLen == 0)
		return -1;

	if(mult == 0)
		mult = 1;

	digit = *str - '0';

	while(digit != 0){
		returnInt += mult * digit;
		mult = mult / 10;
		digit = *(str + i) - '0';
		i++; 
	}

	return returnInt;
}

void clear_buffer(){
	char c;
	while((c = getchar()) != EOF );
}

void exitProcess(){
	int80(14,0,0,0,0,0);
}

void exitThread(){
	int80(29,0,0,0,0,0);
}

void * malloc(int size){
	return ((void *)int80(10,size,0,0,0,0));
}

void printHexadecimal(void * pointer){
	int80(11,(qword) pointer,0,0,0,0);
}

int waitThread(){
	return int80(30,0,0,0,0,0);
}

int getPID(){
	return int80(6,0,0,0,0,0);
}

int getFatherPID(){
	return int80(33,0,0,0,0,0);
}

void thread(void * entryPoint){
	int80(28,entryPoint,0,0,0,0);
}

int startProcess(char * program){
	int i = int80(12, (qword) program,0,0,0,0);
	return i;
}

void echo(char * string){
	nextLine();
	printf("%s", string);
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
	printf("      processRead       processWrite          background          processWriteAndRead");
	nextLine();
	nextLine();
	printf("       producer           consumer            threadTest          proA");
	nextLine();
	nextLine();
	printf("       proB              proC");
	nextLine();
}

void time(){
	int80(9, 0, 0, 0, 0, 0);
	return;
}

void printHeader(){
	int80(24, 0, 0, 0, 0, 0);
}

void killProgram(int pid){
	int ret = int80(25, pid, 0, 0, 0, 0);
	nextLine();		
	if(ret == -1)
		printf("The process with pid %d doesn't exist. Please exec 'ps' command to check.", pid);
	else
		printf("The process with pid %d was successfully removed!", pid);
}

void printMemoryInformation(){
	int80(26, 0, 0, 0, 0, 0);
}

void printMemoryInformationVertical(){
	int80(27, 0, 0, 0, 0, 0);
}

void printProcessTree(){
	int80(34, 0, 0, 0, 0, 0);
}