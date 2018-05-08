#ifndef PROCESS_H
#define PROCESS_H

#include "types.h"
#include "structs.h"

/* Creates a pointer to an struct Process with all needed to run a process */
int createProcess(void * entryPoint, char * nameProcess);

/* Adds process to table process */
void addProcessToPCB(Process newProcess);

ProcessSlot * createSlot(Process newProcess);

void printAllCurrentProcess();

int getProcessFromName(char * procesName);

ProcessSlot * getProcessFromPid(int pid);

#endif