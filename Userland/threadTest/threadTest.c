#include <stdarg.h>
#include <string.h>
#include <types.h>
#include <stdlib.h>
#include <stdio.h>

int flagTask1;

void functionTask1(){
	while(flagTask1 != 0);
	printf("Deleting thread\n");
	exitThread();
}

void functionTask4(){
	printf("Entering thread 1\n");
	exitThread();
}

void functionTask4bis(){
	printf("Entering thread 2\n");
	exitThread();
}

void functionTask4bisbis(){
	printf("Entering thread 3\n");
	exitThread();
}


void functionTask3(){
	int * varThread;
	void * heapSP = heapStartingPoint();
	printf("- Thread: Heap Starting Point: heapSP = ");
	printHexadecimal(heapSP);
	nextLine();
	nextLine();
	printf("Heap starting point is the same in both threads. SAME PROCESS THREADS ---> SAME HEAP\n");
	nextLine();
	printf("- Thread: Now I make a malloc inside the thread... Remember that I made a malloc of size sizeof(int) before so the pointer will value heapSP + 4\n");
	nextLine();
	varThread = malloc(sizeof(int));
	printf("The result is: threadPointer = ");
	printHexadecimal(varThread);
	nextLine();
	nextLine();
	exitThread();
}

int main(void){
	int threads = 0, tCount, t = 0, i = 0;
	int * varMain;
	void * heapSP;
	clear_screen();
	printf("--- THREAD TEST ---\n");
	nextLine();
	printfColor(0x045FB4, "1 - Create N threads\n");
	clear_buffer();
	
	do {
		printf("Enter how many threads you want to create followed by ENTER (2-10): ");
		getNum(&threads);
		nextLine();
	} while(threads < 2 || threads > 10);
	
	
	flagTask1 = 1;
	nextLine();
	while(t < threads){
		thread(functionTask1);
		printf("Creating thread %d\n", t + 1);
		t++;
	}
	
	nextLine();
	tCount = threadCount();
	
	if(tCount == (threads + 1)){
		printf("SUCCESS!! There are %d threads, including main one.\n",tCount);
	} else {
		printf("ERROR!! There are %d threads, including main one. That's wrong because we created %d plus main is %d\n",tCount, threads, threads+1);
	}

	printfColor(0x045FB4, "\n2 - Deleting threads\n");
	
	do {
		printf("To continue press 1 followed by ENTER: ");
		getNum(&i);
		nextLine();
	} while(i != 1);
	
	nextLine();
	flagTask1 = 0;
	waitThread();
	while(i<60000000){
    	i++;
    }

	tCount = threadCount();

	if(tCount == 1){
		printf("SUCCESS!! There is only %d thread, main one.\n",tCount);
	} else {
		printf("ERROR!! There are %d threads, including main one\n", tCount);
	}

   	printfColor(0x045FB4, "\n3 - Two threads (or more) share their heap\n");
	i=0;
	
	do {
		printf("To continue press 1 followed by ENTER: ");
		getNum(&i);
		nextLine();
	} while(i != 1);
	nextLine();
	printf("I make the first malloc of the program in order to get given a heap. It size is of sizeof(int) = 4...\n");
	malloc(sizeof(int));
	nextLine();
	
	printf("Now I'll print heap starting point in two different threads...\n");
   	printf("- Main thread: Heap Starting Point: heapSP = ");
   	heapSP = heapStartingPoint();
	printHexadecimal(heapSP);
	
   	thread(functionTask3);
   	printf("\nCreating thread 1...\n");

	waitThread();
	while(threadCount() != 1);

    printf("- Main thread: Now I make a malloc on main thread of size sizeof(int).. I recently made malloc inside the thread so if the heap is shared, my pointer will value threadPointer + 4 \n");
    varMain = malloc(sizeof(int));
    nextLine();
    printf("The result is: mainPointer = ");
	printHexadecimal(varMain);
	nextLine();

	printfColor(0x045FB4, "\n4 - Threads schedule in order\n");
   	i=0;
	do {
		printf("To continue press 1 followed by ENTER: ");
		getNum(&i);
		nextLine();
	} while(i != 1);

	nextLine();
	printf("- Main thread: If scheduler works OK, the order will be: \n");
	printf("1 - MAIN\n");
	printf("2 - THREAD 1\n");
	printf("3 - THREAD 2\n");
	printf("4 - THREAD 3\n");
	printf("5 - RETURNING TO MAIN\n");
	
	nextLine();

   	thread(functionTask4);
   	printf("Creating thread 1...\n");
   	thread(functionTask4bis);
   	printf("Creating thread 2...\n");
   	thread(functionTask4bisbis);
   	printf("Creating thread 3...\n");
   	nextLine();
   	waitThread();
   	while(threadCount() != 1);
   	printf("Returning to main thread\n");

	nextLine();
  	clear_buffer();
	exitProcess();
	return 0;
}