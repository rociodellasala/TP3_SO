#ifndef STDIO_H
#define STDIO_H

#define MAX_SIZE 2000
#define exit 2

/* Prints string with format */
void printf(const char *, ...);

/* Prints character */
void putchar(unsigned char);

/* Gets a character, an unsigned char, from stdin */
char getchar();

/* Deletes the last character from stdin */
void backspace();

/* Clears the screen, displaying an empty screen */
void clear_screen();

/* Clears the screen, displaying an the prompt to write on terminal */
void clear_terminal();

/* Prints a new line */
void nextLine();

/* Prints a new line with prompt */
void nextTerminalLine();

/* Changes font color shown on terminal */
int changeFontColor(char *);

#endif
