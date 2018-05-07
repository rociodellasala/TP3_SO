#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "structs.h"

#define INVALID_PID -1

/*Creates a pointer to an struct Process with all needed to run a process*/
int createProcess(void * entryPoint, char * nameProcess);

/*Add process to table Process*/
void addProcessToPCB(Process newProcess);

void startProcess(void * entryPoint, char * nameProcess);

void runScheduler();

void * switchUserToKernel(void * esp);

void * switchKernelToUser();


void printAllCurrentProcess();

ProcessSlot * searchRunningProcess();

void terminateProcess(int PID);

void initializeKernelStack();

void * fillStackFrame(void * entryPoint, void * baseStack);

int getCurrentPid();

void removeFinishedProcess();

ProcessSlot * getProcessWithPid(int pid);

void removeProcess(int pid);

#endif
