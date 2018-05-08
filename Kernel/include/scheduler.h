#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "structs.h"

#define INVALID_PID -1

/* */
void startProcess(void *, char *);

/* */
void runScheduler();

/* */
void * switchUserToKernel(void *);

/* */
void * switchKernelToUser();

/* */
ProcessSlot * searchRunningProcess();

/* */
void terminateProcess(int);

/* */
void initializeKernelStack();

/* */
int getCurrentPid();

/* */
void removeFinishedProcess();

/* */
void removeProcess(int);

/* */
void blockProgram();

#endif
