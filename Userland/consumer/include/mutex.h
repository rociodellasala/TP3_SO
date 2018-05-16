#ifndef MUTEX_H
#define MUTEX_H

#define LOCK -1
#define SUCCESFUL 0

int mutex(char * mutexName);

void wait(int index);

void signal(int index);

void freeMutex(int index);

#endif
