#ifndef STRUCTS_H
#define STRUCTS_H

#define MAX_PAGES 20
#define MAX_PROCESS_NAME 50
#define PAGES_KERNEL_HEAP 96

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
  	char processName[MAX_PROCESS_NAME];
  	p_heapPage heap;
  	void * pages[MAX_PAGES];
}Process;

#endif