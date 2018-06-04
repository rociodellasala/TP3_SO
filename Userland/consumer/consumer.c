#include <stdlib.h>
#include <mutex.h>
#include <types.h>
#include <stdio.h>

#define INITIALIZED 1
#define BUFFER_SIZE 10

static char * buffer = (void *) 0x700060;
static int * index = (void *) 0x700050;
static int * initialization = (void *) 0x700040;
static int * producers = (void *) 0x700020;
static int * consumers = (void *) 0x700000;

int main (void){

	int mutexProducer = mutex("Producer");
	int mutexConsumer = mutex("Consumer");
	int iteration = 0;
	int consumer = *consumers;

	/*clear_screen();*/
	if( *initialization != INITIALIZED){
		*initialization = INITIALIZED;
		*index = 0;
		*producers = 0;
		*consumers = 0;
		wait(mutexConsumer);
		wait(mutexProducer);
	}

	*consumers += 1;
	printfColor(0x0000,"\n");

	while(1){
		printfColor(0xFE2E2E,"Consumiendo con consumer: %d", consumer);
        if (*index == 0 || *index < 0) 
        {
        	printfColor(0xFE2E2E,"\nEl buffer esta vacio\n");
        	sleep(2);
            wait(mutexConsumer);
            printfColor(0xFE2E2E,"Consumiendo con consumer: %d", consumer);
        }
        *(buffer + (*index)) = 0;
        *index -= 1;
        iteration++;

       	printfColor(0xFE2E2E," BUFFER: [ %s ]\n", buffer);
       	sleep(3);
        if (*index == BUFFER_SIZE - 1) 
        {
            signal(mutexProducer);
        }
	}

	exitProcess();
	return 0;
}
