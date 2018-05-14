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

void printHeaderInfo();

void moveFreeArray(int * freeArray);

void releaseStructs(ProcessSlot * slot);

void releaseProcessSlot(ProcessSlot * slot);

void releaseProcessHeap(ProcessSlot * slot);

void releaseHeapStruct(p_heapPage heap);

void releasePipeSlot(ProcessSlot * slot);

void releasePipeStruct(p_pipe pipe);



#endif

