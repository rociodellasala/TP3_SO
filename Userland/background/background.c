#include "types.h"
#include "string.h"
#include "stdlib.h"
#include "stdio.h"


int main() {
	int i;
	for(i = 0; i < 15; i++)
		printMsg(0);

	nextLine();
	
	clear_buffer();
	exitProcess();
	return 0;
}


