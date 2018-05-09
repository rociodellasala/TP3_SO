#ifndef STDLIB_H
#define STDLIB_H

/* Converts an int into string */
void intToString(int, char *);

/*Return a void * pointer to an amount of reserved memory*/
void * malloc(int);

void clear_buffer();

/*Print the hexadecimal number of a pointer*/
void printHexadecimal(void *);

#endif
