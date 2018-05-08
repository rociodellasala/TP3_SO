#ifndef STRUCTS_H
#define STRUCTS_H

#include "types.h"

#define MAX_PAGES 20
#define MAX_PROCESS_NAME 50
#define PAGES_KERNEL_HEAP 96
#define MAX_MESSAGE_LENGHT 100

#define FOREGROUND 0
#define BACKGROUND 1

#define RUNNING 2
#define READY 3
#define LOCKED 4
#define FINISHED 5

typedef int (*EntryPoint)();

typedef struct kernelHeapPage{
	int occupiedBytes;
	int freeBytes;
	void * pageAddress;
}kernelHeapPage;

typedef struct kernelHeapHeader{
	int nextPage;
	kernelHeapPage kernelHeapPages[PAGES_KERNEL_HEAP];
}kernelHeapHeader;

typedef struct heapPage * p_heapPage;

typedef struct heapPage{
  void * currentPage;
  int occupiedBytes;
  int freeBytes;
  p_heapPage nextHeapPage;
}heapPage;

typedef struct s_pipe{
  int processOnePID;
  int processTwoPID;

  boolean processOneRead;
  boolean processOneWrite;
  boolean processTwoRead;
  boolean processTwoWrite;
  char message[MAX_MESSAGE_LENGHT];
  int messageIndex;

  boolean mutex;
}s_pipe;

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
    p_pipe pipe;
}Process;

typedef struct ProcessSlot{
    struct ProcessSlot * next;
    Process process;
}ProcessSlot;

#endif