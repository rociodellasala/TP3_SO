#include "stdlib.h"
#include "mutex.h"
#include "types.h"
#include "stdio.h"

#define INITIALIZED 1
#define BUFFER_SIZE 25

extern qword int80(qword rdi, qword rsi, qword rdx, qword rcx, qword r8, qword r9);

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

	while(1){
		/*printf("Estoy consumiendo buffer con consumer: %d\n", consumer);*/
        if (*index == 0) 
        {
        	/*printf("El buffer esta vacio\n");*/
            wait(mutexConsumer);
        }

        *index -= 1;
        iteration++;

       	/*printf("Char obtenido de buffer: %c ", *(buffer + *index));
        printf(" Iteracion:%d",iteration);
        printf(" En el indice del buffer:%d\n",*index);*/

        if (*index == BUFFER_SIZE - 1) 
        {
        	/*printf("Levanto al productor\n");*/
            signal(mutexProducer);
        }
	}

	exitProcess();
	return 0;
}
