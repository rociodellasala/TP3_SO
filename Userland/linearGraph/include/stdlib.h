#ifndef STDLIB_H
#define STDLIB_H

#include "types.h"

/* Converts an int to string */
void intToString(int, char *);

/* Consumes buffer before exit */
void clear_buffer();

/* Makes a syscall in order to exit */
void exitProcess();

/* Reads a string as an int */
char * readInt(char *, int *);

/* Reads until the end of line */
char* readLine();

/* Returns true if the character is a number */
int isNum(char);

/* Draws the x-axis and y-axis */
void coordinates();

/* Reads a number */
int getNum(int *);

#endif
