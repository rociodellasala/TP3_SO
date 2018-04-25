#ifndef NAIVE_CONSOLE_H
#define NAIVE_CONSOLE_H

#include <types.h>

/* Converts the specified value into decimal and prints it */
void printDec(qword value);

/* Converts the specified value into hexadecimal and prints it */
void printHex(qword value);

/* Converts the specified value into binary and prints it */
void printBin(qword value);

/* Converts the specified value into specified base and prints it */
void printBase(qword value, dword base);

#endif
