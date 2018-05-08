#ifndef CONVERTER_H
#define CONVERTER_H

#include "types.h"

/* Converts the specified value into decimal and prints it */
void printDec(qword);

/* Converts the specified value into hexadecimal and prints it */
void printHex(qword);

/* Converts the specified value into binary and prints it */
void printBin(qword);

/* Converts the specified value into specified base and prints it */
void printBase(qword, dword);

/* Converts the specified value into specified base */
dword uintToBase(qword, char *, dword);

/* Converts int to string */
void intToString(int, char *);

#endif
