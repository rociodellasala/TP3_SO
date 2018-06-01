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
ThreadSlot * createThread(void * entryPoint);

ThreadSlot * createThreadSlot(Thread thread);

/* Displays all the current process existing on the table process */
void printAllCurrentProcess();

/* Returns PID of the specified name */
int getProcessFromName(char *);

/* Returns the slot of the specified PID */
ProcessSlot * getProcessFromPid(int);

#endif
