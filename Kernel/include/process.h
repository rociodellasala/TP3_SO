#ifndef PROCESS_H
#define PROCESS_H

#include "types.h"
#include "structs.h"

/* Creates a pointer to an struct Process with all needed to run a process */
int createProcess(void *, char *);

/* Adds process to table process */
void addProcessToPCB(Process);

/* */
ProcessSlot * createSlot(Process);

/* */
void printAllCurrentProcess();

/* */
int getProcessFromName(char *);

/* */
ProcessSlot * getProcessFromPid(int);

#endif
