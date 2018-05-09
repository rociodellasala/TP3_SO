#ifndef STDLIB_H
#define STDLIB_H

/* Converts an int into string */
void intToString(int, char *);

/* Makes a syscall in order to exit */
void exitProcess();

/* Runs a new program */
int startProcess(char *);

/* Displays runnable programs */
void ls();

/* Displays current process running */
void ps();

/* Prints current time */
void time();

#endif
