#include <stdlib.h>
#include <string.h>
#include <types.h>
#include <stdio.h>

void printMsg(int j){
	while(j < 50000000){
		j++;	
	}
	printf("\nSolo si corro en foreground podras leer mi mensaje!");
}

int main() {
	int i;
	for(i = 0; i < 15; i++)
		printMsg(0);

	nextLine();
	
	clear_buffer();
	exitProcess();
	return 0;
}


