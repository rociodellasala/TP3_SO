#ifndef SHELL_H
#define SHELL_H

#define MAX_SIZE 2000
#define exit 2

/* Start the shell */
void start_shell();

/* Gets the command to work in terminal */
int get_command(char * buffer);

/* Calls the command, if it exist */
int call_command(char * function, char * param);

/* Displays help menu for the user */
void printHelp();

/* Displays a line of text */
void echo(char * buffer);

#endif
