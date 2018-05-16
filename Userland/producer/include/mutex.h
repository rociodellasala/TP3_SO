#ifndef MUTEX_H
#define MUTEX_H

#define LOCK -1
#define SUCCESFUL 0

/*Returns the index of a mutex which name is mutexName, otherwise create's a mutex with that name*/
int mutex(char * mutexName);

/*Changes mutex value to false if possible, otherwise block process*/
void wait(int index);

/*Changes mutex value to true if possible, otherwise block process*/
void signal(int index);

/*Release mutex*/
void freeMutex(int index);

#endif
