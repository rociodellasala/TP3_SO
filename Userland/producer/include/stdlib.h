#ifndef STDLIB_H
#define STDLIB_H

#define READ 0
#define WRITE 1
#define BLOCKPROCESS -1

/* Converts an int into string */
void intToString(int, char *);

/* Returns void * pointer to an amount of reserved memory */
void * malloc(int);

/* Call system call to terminate process*/
void exitProcess();

/* Clears all buffer*/
void clear_buffer();

/* Print the hexadecimal number of a pointer*/
void printHexadecimal(void *);

/* Call system call to get process ID*/
int getPID();

/* Call system call to create a pipe*/
int pipe(char *);

/* Call system call to write through a pipe*/
int write(int, char *, int);

/* Call system call to read through a pipe*/
int read(int, char *, int);

/* Call system call to make a process unable to write or read*/
void close(int, int);

/* Call system call to make a process able to write or read*/
void open(int, int);

#endif
