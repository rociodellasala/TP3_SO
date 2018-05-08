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
void * findAvaiableHeapKernelPage(int);;

/* */
void * malloc_heap(int);

/* */
p_heapPage findAvaiableHeapPage(p_heapPage, int);

/* */
void * findFreePointer(p_heapPage);

#endif

