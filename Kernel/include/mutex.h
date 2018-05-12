#ifndef MUTEX_H
#define MUTEX_H

#include "types.h"
#include "structs.h"

#define MAX_MUTEX_SLOT 100
#define INVALID_PROCESS -1
#define INVALID_INDEX -1
#define LOCK -1;
#define SUCCESFUL 0;

void initiliazeMutexes();

p_mutex createMutex();

int getFreeMutex(char * mutexName);

int getMutexByName(char * mutexName);

void freeMutex(int index);

int wait(int index);

int signal(int index);

boolean isInQueue(int * queue);

void removeFromQueue(int * queue);

void addToQueue(int * queue);

#endif
