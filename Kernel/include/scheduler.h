#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "structs.h"

#define INVALID_PID -1

/* Starts shell process as init one */
void startProcess(void *, char *);

/* Changes current running process if number of ticks equals quantum */
void runScheduler();

/* Returns kernel stack in order to run kernel code */
void * switchUserToKernel(void *);

/* Returns user stack of the next process to run */
void * switchKernelToUser();

/* Searchs into the table process with process is currently running */
ProcessSlot * searchRunningProcess();

/* Returns PID of the current process */
int getCurrentPid();

/* Removes from the table process the one that has already finished */
void removeFinishedProcess();

/* Sets the pointer in order to run the next process. Removes from the table process the one that has already finished */
void removeProcess(int);

/* Same as removeProcess but by terminal */
int removeProcessFromTerminal(int);

/* Blocks a process */
void blockProcess(int pid);

/* Unblocks a process */
void unblockProcess(int pid);

Thread blockThread(Thread thread);

void checkIfThreadChange();

void nextThread();

Process deleteThreadFromProcess(Process);

void sleep(int segs);

void changeProcessTree(Process process);

#endif
