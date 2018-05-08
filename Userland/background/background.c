#include <exception.h>
#include <types.h>
#include <shell.h>
#include "./include/stdio.h"
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>

testA(int i, int j){
	while(j < 50000000){
		j++;	
	}
	printf("hola\n");
}

void clear_buffer(){
	char c;
	while(c = getchar() != EOF );
}

int main() {
	testA(1, 4);
	testA(1, 4);
	testA(1, 4);
	testA(1, 4);
	testA(1, 4);
	testA(1, 4);
	testA(1, 4);
	testA(1, 4);
	testA(1, 4);
	testA(1, 4);
	testA(1, 4);
	testA(1, 4);
	testA(1, 4);
	testA(1, 4);
	testA(1, 4);
	testA(1, 4);
	testA(1, 4);
	testA(1, 4);
	testA(1, 4);
	testA(1, 4);
	
	clear_buffer();
	exitProgram();
}




void exitProgram(){
	int80(14,0,0,0,0);
}

