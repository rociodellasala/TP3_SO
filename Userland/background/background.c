#include <exception.h>
#include <types.h>
#include <shell.h>
#include "./include/stdio.h"
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>

printMsg(int j){
	while(j < 50000000){
		j++;	
	}
	printf("\nSolo si corro en foreground podras leer mi mensaje!");
}

void clear_buffer(){
	char c;
	while(c = getchar() != EOF );
}

int main() {
	printMsg(0);
	printMsg(0);
	printMsg(0);
	printMsg(0);
	printMsg(0);
	printMsg(0);
	printMsg(0);
	printMsg(0);
	printMsg(0);
	printMsg(0);
	printMsg(0);
	printMsg(0);
	printMsg(0);
	printMsg(0);
	printMsg(0);
	printMsg(0);
	printMsg(0);
	printMsg(0);
	printMsg(0);
	printMsg(0);
	printMsg(0);
		printMsg(0);
	printMsg(0);
	printMsg(0);
	printMsg(0);
	printMsg(0);

	
	
		
	
	clear_buffer();
	exitProgram();
}




void exitProgram(){
	int80(14,0,0,0,0);
}

