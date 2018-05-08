#ifndef KERNEL_H
#define KERNEL_H

#include "structs.h"

void clearBSS(void *, qword);

void * getStackBase();

void * initializeKernelBinary();

/* Allocs a page for the kernel stack */
void initializeKernelStack();

#endif
