#ifndef STDLIB_H
#define STDLIB_H

/* Converts an int into string */
void intToString(int num, char * str);

void printHexadecimal(void * pointer);

/* Consumes buffer before exit */
void clear_buffer();

/* Makes a syscall in order to exit */
void exitProcess();

void printMsg(int j);

#endif
