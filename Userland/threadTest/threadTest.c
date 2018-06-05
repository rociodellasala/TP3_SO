#include <stdarg.h>
#include <string.h>
#include <types.h>
#include <stdlib.h>
#include <stdio.h>

void (*ptr_fun) ();

void function1(){
	int i, j=0;
	for(i=0; i<40; i++){
		while(j < 1000000){j++;}
		printfColor(0xFE2E2E," THREAD 1 - a: %d\n", i);
	}
	printfColor(0xFE2E2E," ---- THREAD 1 FINISHING....\n");
	exitThread();
}

void function2(){
	int i, j=0;
	for(i=0; i<20; i++){
		while(j < 1000000){j++;}
		printfColor(0x2E64FE," THREAD 2 - b: %d\n", i);
	}
	printfColor(0x2E64FE," ---- THREAD 2 FINISHING....\n");
	exitThread();
}

void function3(){
	int i, j=0;
	for(i=0; i<30; i++){
		while(j < 1000000){j++;}
		printfColor(0x9AFE2E," THREAD 3 - c: %d\n", i);
	}
	printfColor(0x9AFE2E," ---- THREAD 3 FINISHING....\n");
	exitThread();
}

int main(void){
	int threads, i = 0, start = 0;
	clear_screen();
	printf("--- THREAD TEST ---\n");
	nextLine();
	printf("1 - First we're going to create 3 threads on this process.\n");
	printf("2 - Then, each of them will print the value of a variable: a (THREAD 1, RED), b(THREAD 2, BLUE) or c (THREAD 3, GREEN). To do that the kernel will schedule between them and the main process.\n");
	printf("3 - After, the main process will wait until all of them finish in order to finish too.\n");
	nextLine();
	printf("NOTE: THREAD 1 will print 40 values, THREAD 2 will print 30 values and THREAD 3 will print 35 values.\n");
	nextLine();
	clear_buffer();
	do{
		printf("To start the test please press 1: ");
		getNum(&start);
		nextLine();
	} while(start != 1);

	printfColor(0xFE2E2E,"Creating thread 1...\n");
	printfColor(0x2E64FE,"Creating thread 2...\n");
	printfColor(0x9AFE2E,"Creating thread 3...\n");

 	thread(function1);
 	thread(function2);
 	thread(function3);

    waitThread();
    printf(" --- MAIN THREAD STATUS: Locked. Main thread will wait until all threads finished\n");
    while(i<60000000){
    	i++;
    }

  	printf(" --- MAIN THREAD : All threads are finished, so now main thread can finish too..\n");
  	clear_buffer();
	exitProcess();
	return 0;
}

