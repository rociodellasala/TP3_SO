#ifndef STRUCTS_H
#define STRUCTS_H

#include <types.h>

#define MAX_PAGES 20
#define MAX_PROCESS_NAME 50
#define PAGES_KERNEL_HEAP 96

#define RUNNING 1
#define READY 2
#define FINISHED 3

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

typedef struct Process{
    int PID;
    int status;
    char processName[MAX_PROCESS_NAME];
    void * pages[MAX_PAGES];
    void * startingPoint;
    void * userStack;
    void * baseStack;
    p_heapPage heap;
}Process;

typedef struct ProcessSlot{
    struct ProcessSlot * next;
    Process process;
}ProcessSlot;

typedef int (*EntryPoint)();

typedef struct StackFrame {
  qword gs;
  qword fs;
  qword r15;
  qword r14;
  qword r13;
  qword r12;
  qword r11;
  qword r10;
  qword r9;
  qword r8;
  qword rsi;
  qword rdi;
  qword rbp;
  qword rdx;
  qword rcx;
  qword rbx;
  qword rax;

  qword rip;
  qword cs;
  qword eflags;
  qword rsp;
  qword ss;
  qword base;
} StackFrame;


#endif