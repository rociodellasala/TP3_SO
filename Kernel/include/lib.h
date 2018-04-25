#ifndef LIB_H
#define LIB_H

#include <types.h>

void * memset(void * destination, dword character, qword length);

void * memcpy(void * destination, const void * source, qword length);

char * cpuVendor(char * result);

#endif
