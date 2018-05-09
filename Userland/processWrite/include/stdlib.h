#ifndef STDLIB_H
#define STDLIB_H

#define READ 0
#define WRITE 1

/* Converts an int into string */
void intToString(int, char *);

void * malloc(int);

void exitProcess();

void clear_buffer();

void printHexadecimal(void *);

int getPID();

int pipe(char *);

int write(int, char *, int);

int read(int, char *, int);

void close(int, int);

void open(int, int);

#endif
