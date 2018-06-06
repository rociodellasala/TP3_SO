#ifndef SHELL_H
#define SHELL_H

#define MAX_SIZE 2000
#define MAX_COMMAND_SIZE 100
#define exit 2

#include "types.h"

/* Start the shell */
void start_shell();

/* Gets the command to work in terminal */
int get_command(char *);

/* Calls the command, if it exist */
int call_command(char *, char *);

/* Displays help menu for the user */
void printHelp();

/* Looks if there are two process to execute */
boolean hasTwoProcess(char * function);

void getBothProcess(char * function, char * processOne, char * processTwo);

#endif
