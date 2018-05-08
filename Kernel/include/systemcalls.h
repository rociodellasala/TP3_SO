#ifndef SYSTEM_CALLS_H
#define SYSTEM_CALLS_H

#include "types.h"

/* Loads system calls of our program */
void load_systemcalls();

/* Executes the syscall acording to rdi value */
void syscallHandler(qword, qword, qword, qword, qword, qword);

#endif
