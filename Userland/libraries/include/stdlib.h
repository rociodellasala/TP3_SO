#ifndef STDLIB_H
#define STDLIB_H

/* Turns an int into a string */
void intToString(int num, char * str);

/* Turns a string into an int */
int stringToInt(char * str);

/* Clears all buffer */
void clear_buffer();

/* Call system call to start process */
int startProcess(char * program);

/* Call system call to terminate process */
void exitProcess();

/* Returns void * pointer to an amount of reserved memory */
void * malloc(int);

/* Print the hexadecimal number of a pointer */
void printHexadecimal(void *);

/* Call system call to get process ID */
int getPID();

/* Prints a string in console */
void echo(char * string);

/* Prints information about all process */
void ps();

/* Prints all programs that can be executed */
void ls();

/* Prints the actual time */
void time();

/* Prints critical information for debbugers */
void printHeader();

/* Kill a program by pid */
void killProgram(int pid);

/* Call sys call to print memory tree information */
void printMemoryInformation();

#endif
