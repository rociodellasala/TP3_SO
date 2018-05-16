#ifndef HEAP_H
#define HEAP_H

#include "structs.h"

#define PAGE_SIZE 4096

/*Initiaze kernel's heap with an amount of pages*/
void initializeKernelHeap();

/*Prints all the pages reserved by kernel's heap*/
void printKernelHeap();

/*Creates a pointer structure to a s_heapPage structure*/
p_heapPage createHeapPage();

/*Finds avaible memory in kernel's heap to store structures*/
void * findAvaiableHeapKernelPage(int);

/*Returns a void * pointer to an amount of avaible memory in user process's heap*/
void * malloc_heap(int);

/*Retuns the starting address of a heap page with X avaible bytes to reserve memory*/
p_heapPage findAvaiableHeapPage(p_heapPage, int);

/*Returns a void * pointer in a heap page that has X bytes free of memory*/
void * findFreePointer(p_heapPage);

/*Shows vital information of scheduling and OS modifications*/
void printHeaderInfo();

/*Moves all the array one position to left*/
void moveFreeArray(int * freeArray);

/*Release all kernel structs use for scheduling, memory managment and IPC*/
void releaseStructs(ProcessSlot * slot);

/*Release struct used for scheduling*/
void releaseProcessSlot(ProcessSlot * slot);

/*Release struct used for memory managment of a process*/
void releaseProcessHeap(ProcessSlot * slot);

/*Release all structs used for memory managment of a process*/
void releaseHeapStruct(p_heapPage heap);

/*Release struct used for IPC of a process*/
void releasePipeSlot(ProcessSlot * slot);

/*Release all structs used for IPC of a process*/
void releasePipeStruct(p_pipe pipe);



#endif

