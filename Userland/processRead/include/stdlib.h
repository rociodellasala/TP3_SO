#ifndef STDLIB_H
#define STDLIB_H

#define READ 0
#define WRITE 1

/* Converts an int into string */
void intToString(int num, char * str);

void * malloc(int size);

void printHexadecimal(void * pointer);

int getPID();

int pipe(char * connectingProcessName);

int write(int pid,char * message, int messageLenght);

int read(int pid,char * messageDestination, int charsToRead);

void close(int pid, int operation);

void open(int pid, int operation);

#endif
