#ifndef STRINGS_H
#define STRINGS_H

#include "../types.h"

/*Gets string length*/
int strlen(const char * str);

/*Returns if two strings are equal*/
boolean strcmp(char * s1, char * s2);

/*Returns true if 'c' es a space*/
boolean isspace(char c);

#endif
