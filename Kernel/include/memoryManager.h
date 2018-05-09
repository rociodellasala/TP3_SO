#ifndef MEMORYMANAGER_H
#define MEMORYMANAGER_H

#include "structs.h"

#define FREEPAGES 300
#define PAGEQUANTITY 262144 /* 1GB divided into 4KB */

struct memoryPage{
     void * startingMemory;
     int occupied;
};

struct memoryFreeStack{
     void * memoryFree[FREEPAGES];
     int size;
};

/* Initialize memory manager by splitting the memory in pages of 4KB and initialize stack for released pages */ 
void initializeMemoryManager();

/*  Splits memory in pages of 4KB */
void splitMemory();

/*Initialize all the pages that are occupied by kernel and Modules*/
void markOccupiedPages();

/*Just prints all the starting addresses of the pages*/
void printMemoryPages();

/*Just prints all the starting addresses of the released pages*/
void printFreePages();

/* Returns an unused page */
void * allocPage();

/* Search for a free page */
void * searchForFreePage();

/* Puts the released page in stack for optimization */
void releasePage(Process);

/*Release the especefic page that was reserved for user program stack memory*/
void releaseStack(void *);

/*Release all the pages reserved for the heap memory of the user program*/
void recursiveRealeseHeap();

#endif
