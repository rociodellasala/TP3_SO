#ifndef STDLIB_H
#define STDLIB_H

/* Converts an int into string */
void intToString(int, char *);

/*Converts a string into Int */
int stringToInt(char * str);

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

/*Prints vital information for debbuging, only SO developers*/
void printHeader();

/*Terminates a specific process by PID*/
void killProgram(int pid);

#endif
