#ifndef HEAP_H
#define HEAP_H

#include "structs.h"

#define PAGE_SIZE 4096

/* */
void initializeKernelHeap();

/* */
void printKernelHeap();

/* */
p_heapPage createHeapPage();

/* */
void * findAvaiableHeapKernelPage(int size);;

/* */
void * malloc_heap(int size);

/* */
p_heapPage findAvaiableHeapPage(p_heapPage firstPage, int size);

/* */
void * findFreePointer(p_heapPage heapPage);

#endif

