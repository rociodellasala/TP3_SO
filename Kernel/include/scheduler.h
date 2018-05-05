#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "structs.h"

/*Creates a pointer to an struct Process with all needed to run a process*/
void createProcess(void * entryPoint, char * nameProcess);

/*Add process to table Process*/
void addProcess(Process newProcess);

void printAllCurrentProcess();

Process getCurrentProcess();

#endif
