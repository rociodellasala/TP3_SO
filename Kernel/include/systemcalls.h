#ifndef SYSTEM_CALLS
#define SYSTEM_CALLS

#include <types.h>

/* Loads system calls of our program */
void load_systemcalls();

/* Executes the syscall acording to rdi value */
void syscall_handler(qword rdi, qword rsi, qword rdx, qword rcx, qword r8, qword r9);

#endif
