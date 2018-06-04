#ifndef STRINGS_H
#define STRINGS_H

#include "types.h"

/* Returns the length of the specified string */
int strlen(const char *);

/* Compares both strings and returns if they are equal */
boolean strcmp(char *, char *);

/* Compares both strings and returns if their first num characters are equal */
boolean strncmp(char *, char *, int);

/* Copy the string from source to dest */
char * strcpy(char *, const char *);

/* Copy n chars from source to dest */
char * strncpy(char *, const char *, int);

/* Concatenates two strings */
char * strcat(char * dest, const char * source);

/* Returns the char located at the position i of the specified string */
char charAtPos(char *, int);

/* Concatenates important information for memoryManager nodes */
void getNodeInfo(char * vector, char * processName, int pid, char * processInfo);

#endif
