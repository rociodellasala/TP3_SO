#ifndef HEAP_H
#define HEAP_H

#define PAGE_SIZE 4096


#include "structs.h"

void initializeKernelHeap();

void printKernelHeap();

p_heapPage createHeapPage();

p_heapPage startEmptyHeap();

void * malloc_heap(int size, char * processName);

int searchProcessStruct(char * processName);

void * findAvaiableHeapKernelPage(int size);

p_heapPage findAvaiableHeapPage(p_heapPage firstPage, int size, int numberProcess);

void * findFreePointer(p_heapPage heapPage);

#endif