#include <stdlib.h>
#include <string.h>
#include <types.h>
#include <stdio.h>

void printMsg(int j){
	while(j < 50000000){
		j++;	
	}
	printf("Only if I run in foreground you will read my message!\n");
}

int main() {
	int i;
	char * msg = malloc(200);
	nextLine();
	strcpy(msg,"asd");
	printf("\n--- BACKGROUND ---\n");
	nextLine();

	for(i = 0; i < 15; i++)
		printMsg(0);

	nextLine();
	
	clear_buffer();
	while(1);
	exitProcess();
	return 0;
}


