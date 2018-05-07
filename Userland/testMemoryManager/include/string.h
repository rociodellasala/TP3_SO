#ifndef STRINGS_H
#define STRINGS_H

/* Returns the length of the specified string */
int strlen(const char * str);

/* Compares both strings and returns if they are equal */
boolean strcmp(char * str1, char * str2);

/* Compares both strings and returns if their first num characters are equal*/
boolean strncmp(char * str1, char * str2, int num);

/* Copy the string from source to dest*/
char * strcpy(char * dest,const char * source);

#endif
