#ifndef STRUCTS_H
#define STRUCTS_H

#include "types.h"

#define MAX_PAGES 20
#define MAX_PROCESS_NAME 50
#define PAGES_KERNEL_HEAP 96
#define MAX_MESSAGE_LENGHT 100
#define MAX_QUEUED_PROCESS 20
#define MAX_MUTEX_NAME 20

#define FOREGROUND 0
#define BACKGROUND 1

#define RUNNING 2
#define READY 3
#define LOCKED 4
#define FINISHED 5

#define MAX_PROCESS_SLOT 100
#define MAX_MUTEX_SLOT 200
#define MAX_PIPES 10
#define MAX_HEAP_SLOT 20
#define MAX_FREE 10
#define INVALID_LAST_FREE_SLOT -1

typedef int (*EntryPoint)();

typedef struct s_heapPage * p_heapPage;

typedef struct s_heapPage{
  void * currentPage;
  int occupiedBytes;
  int freeBytes;
  p_heapPage nextHeapPage;
}s_heapPage;

typedef struct s_pipe{
  int pipePID;

  int processOnePID;
  int processTwoPID;
  char processTwoName[MAX_PROCESS_NAME];

  boolean processOneRead;
  boolean processOneWrite;
  boolean processTwoRead;
  boolean processTwoWrite;
  char message[MAX_MESSAGE_LENGHT];
  int messageIndex;

  int mutex;
}s_pipe;

typedef struct s_mutex
{
  boolean avaiable;
  boolean mutexValue;
  char idName[MAX_MUTEX_NAME];
  int pidQueueWait[MAX_QUEUED_PROCESS];
  int pidQueueSignal[MAX_QUEUED_PROCESS];
}s_mutex;

typedef s_mutex * p_mutex;

typedef s_pipe * p_pipe;

typedef struct Process{
    int PID;
    int status;
    int foreground;
    char processName[MAX_PROCESS_NAME];
    void * pages[MAX_PAGES];
    void * startingPoint;
    void * userStack;
    void * baseStack;
    p_heapPage heap;
    p_pipe pipes[MAX_PIPES];
    int pipeIndex;
}Process;

typedef struct ProcessSlot{
    struct ProcessSlot * next;
    Process process;
}ProcessSlot;

typedef struct kernelHeapHeader{
  void * startingAddress;
  int pages;
  int lastProcessSlot;
  int lastProcessSlotFree[MAX_FREE];
  ProcessSlot allProcessSlots[MAX_PROCESS_SLOT];
  int lastMutexSlot;
  int lastMutexSlotFree[MAX_FREE];
  s_mutex allMutex[MAX_MUTEX_SLOT];
  int lastPipeSlot;
  int lastPipeSlotFree[MAX_FREE];
  s_pipe allPipesSlots[MAX_PIPES * MAX_PROCESS_SLOT];
  int lastHeapSlot;
  int lastHeapSlotFree[MAX_FREE];
  s_heapPage allHeapSlots[MAX_HEAP_SLOT * MAX_PROCESS_SLOT];
}kernelHeapHeader;

#endif
