#ifndef STRINGS_H
#define STRINGS_H

#include "types.h"

#define NULL 0

/* Returns the length of the specified string */
int strlen(const char *);

/* Compares both strings and returns if they are equal */
boolean strcmp(char *, char *);

/* Compares both strings and returns if their first num characters are equal*/
boolean strncmp(char *, char *, int);

/* Copy the string from source to dest*/
char * strcpy(char *, char *);

/* Copy n chars from source to dest*/
char * strncpy(char * dest, char * source,int lenght);

/* Converts an int into string */
void intToString(int, char *);

/* Converts a string into an int*/
int stringToInt(char * str);

/* Concatenates two strings */
char * strcat(char * dest, const char * source);

/* Search for the position of a string in other string */
char * strsch(const char * source, const char * strSearched);

#endif
