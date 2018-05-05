#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "structs.h"

#define INVALID_PID -1

/*Creates a pointer to an struct Process with all needed to run a process*/
int createProcess(void * entryPoint, char * nameProcess);

/*Add process to table Process*/
void addProcess(Process newProcess);

void printAllCurrentProcess();

ProcessSlot * searchRunningProcess();

void terminateProcess(int PID);

#endif
