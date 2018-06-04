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
	int producer = *producers;

	if( *initialization != INITIALIZED){
		*initialization = INITIALIZED;
		*index = 0;
		*producers = 0;
		*consumers = 0;
		wait(mutexConsumer);
		wait(mutexProducer);
	}

	*producers += 1;
	printfColor(0x0000,"\n");

	while(1){
		printfColor(0x9AFE2E,"Estoy produciendo buffer con producer: %d", producer);
        if(*index == BUFFER_SIZE) 
        {
        	printfColor(0x9AFE2E,"\nBuffer completo\n");
            wait(mutexProducer);
            printfColor(0x9AFE2E,"Estoy produciendo buffer con producer: %d", producer);
        }
        *(buffer + (*index)) = 'a';
        *index += 1;
        printfColor(0x9AFE2E,"  BUFFER: [ %s ]\n", buffer);
        sleep(3);
        if (*index == 1) 
        {
            signal(mutexConsumer);
        }
	}

	exitProcess();
	return 0;
}
