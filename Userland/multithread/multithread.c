#include <stdarg.h>
#include <string.h>
#include <types.h>
#include <stdlib.h>
#include <stdio.h>

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
	printf("--- MULTITHREADING PROCESS ---\n");
	nextLine();
	printf("The aim of this process is to show that the scheduler alternates between all the threads correctly (respecting the order in which they were created and also their status).\n"); 
	printf("In addition, the context of each thread is unique and it is restored correctly every time it returns to its execution. If the scheduler was running thread 1 (for ex: it was printing number 38) and it is interrupted, when the execution is restored, it will print the number 39.\n");
	nextLine();
	printfColor(0x045FB4," GUIDE:\n");
	nextLine();
	printf(" 1 - First we're going to create 3 threads on this process.\n");
	printf(" 2 - Then, each thread will have a variable that will print until it reaches a certain stop value, where it will end. While this happens, each thread can be interrupted by the scheduler, which will run the next thread.\n");
	printf(" 3 - After, the main process will wait until all of them finish in order to finish too.\n");
	nextLine();
	printf("NOTE 1: THREAD 1 will print variable a 40 times in RED, THREAD 2 will print variable b 20 times in BLUE and THREAD 3 will print variable c 30 times in GREEN\n");
	nextLine();
	printf("NOTE 2: If MAIN THREAD appears, it will print in WHITE color, in order to distinguish from the rest\n");
	nextLine();
	clear_buffer();
	do{
		printf("To start please press 1 followed by ENTER: ");
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