#ifndef PROCESS_H
#define PROCESS_H

#include "types.h"
#include "structs.h"

/* Creates a pointer to an struct Process with all needed to run a process */
int createProcess(void *, char *);

/* Adds a process to table process */
void addProcessToPCB(Process);

/* Creates a slot in order to insert a new process into the table process */
ProcessSlot * createSlot(Process);

/* NEW */
ThreadSlot * createThread(void * entryPoint, int threadSize,char * nameProcess,int processPID);

/* NEW */
ThreadSlot * createThreadSlot(Thread);

/* Displays all the current process existing on the table process */
void printAllCurrentProcess();

/* Returns PID of the specified name */
int getProcessFromName(char *);

/* Returns name process of the specified PID */
char * getProcessNameFromPid(int pid);

/* Returns the slot of the specified PID */
ProcessSlot * getProcessFromPid(int);

/* NEW */
ThreadSlot * getLastThreadFromProcess(Process);

/* NEW */
Process addThreadToProcess(int, void *);

void addChild(int childPID, ProcessSlot * slot);

void printProcessTree(ProcessSlot * currentSlot, int lines);

#endif
