#include <stdlib.h>
#include <mutex.h>
#include <types.h>
#include <stdio.h>

#define INITIALIZED 1
#define BUFFER_SIZE 25

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

	while(1){
		/*printf("Estoy produciendo buffer con producer: %d\n", producer);*/
        if(*index == BUFFER_SIZE) 
        {
            wait(mutexProducer);
        }

        *(buffer + (*index)) = 'a';
        *index += 1;
        if (*index == 1) 
        {
            signal(mutexConsumer);
        }
	}

	exitProcess();
	return 0;
}
