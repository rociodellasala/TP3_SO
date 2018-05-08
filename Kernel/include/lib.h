#ifndef LIB_H
#define LIB_H

#include "types.h"

void * memset(void *, dword, qword);

void * memcpy(void *, const void *, qword);

char * cpuVendor(char *);

#endif
