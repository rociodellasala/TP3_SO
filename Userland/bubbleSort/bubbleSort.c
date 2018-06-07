#include <stdarg.h>
#include <string.h>
#include <types.h>
#include <stdlib.h>
#include <stdio.h>

#define CANT 3
#define ARRAYLONG 20

int array[ARRAYLONG] = {79,41,122,19,142,159,162,174,189,198,60,90,61,77,100,1,106,14,16,170};
int limits[2][2] = {{0, ARRAYLONG/2}, {(ARRAYLONG/2)+1, ARRAYLONG}};
int index = 0;

void swap(int *xp, int *yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}
 

void bubbleSort(){
	int i, j, base, n, aux;
	aux = index;
	base = limits[0][index];
	n = limits[1][index]; 

	index++;

   	for (i = 0; i < n-1; i++)         
       for (j = base; j < n-i-1; j++) {
       		printf("Ordering half %d of the array\n", aux);
           if (array[j] > array[j+1])
              swap(&array[j], &array[j+1]);
       }
  	
  	printfColor(0xB40404,"\n- Half of the array is already ordered .. Finishing thread\n");
  	nextLine();
	exitThread();
}


int main(void){
	int start = 0, i;
	clear_screen();
	printf("--- BUBBLE SORT WITH THREADS ---\n");
	
	nextLine();
	
	printf("We have an array of %d numbers ... Let's sort it through two threads\n", ARRAYLONG);
	nextLine();
	printf("We have this array... \n");
	printfColor(0x2E2EFE,"\nArray={");
	for(i = 0; i < ARRAYLONG; i++){
		if(i == ARRAYLONG-1)
			printfColor(0x2E2EFE,"%d}\n", array[i]);
		else
			printfColor(0x2E2EFE,"%d,", array[i]);
	}
	nextLine();
	clear_buffer();

	do{
		start = 0;
		printf("To start please press 1 followed by ENTER: ");
		clear_buffer();
		getNum(&start);
		nextLine();
	} while(start != 1);
	nextLine();
	
	
	thread(bubbleSort);
	printfColor(0x64FE2E,"Creating thread 1...\n");
	thread(bubbleSort);
	printfColor(0xFE642E,"Creating thread 2...\n");
	nextLine();

	while(threadCount() != 1);

	nextLine();

	printf("The array middle-order is: \n Array={");
	for(i = 0; i < ARRAYLONG; i++){
		if(i<ARRAYLONG/2){
			printfColor(0xDA81F5,"%d,", array[i]);
		}else{
			if(i == ARRAYLONG-1)
			printfColor(0xACFA58,"%d}\n", array[i]);
		else
			printfColor(0xACFA58,"%d,", array[i]);
		}
	}
	nextLine();
  	clear_buffer();
	exitProcess();
	return 0;
}
