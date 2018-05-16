#ifndef MUTEX_H
#define MUTEX_H

#include "types.h"
#include "structs.h"


#define INVALID_PROCESS -1
#define INVALID_INDEX -1
#define LOCK -1;
#define SUCCESFUL 0;

/*Creates all the structs of mutexes*/
void initiliazeMutexes();

/*Creates the structs of mutex*/
p_mutex createMutex();

/*Returns the first avaiable mutex*/
int getFreeMutex(char * mutexName);

/*Creates mutex which name is mutexName*/
int getMutexByName(char * mutexName);

/*Release mutex*/
void freeMutex(int index);

/*Change mutex value to false if possible, otherwise blocks process*/
int wait(int index);

/*Change mutex value to true if possible, otherwise blocks process*/
int signal(int index);

/*Search for process pid in a queue*/
boolean isInQueue(int * queue);

/*Removes process pid in a queue*/
void removeFromQueue(int * queue);

/*Add process pid in a queue*/
void addToQueue(int * queue);

#endif
