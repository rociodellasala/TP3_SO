#ifndef STDIO_H
#define STDIO_H

#include "types.h"
#define exit 2

/* Prints character */
void putchar(unsigned char);

/* Gets a character, an unsigned char, from stdin */
char getchar();

/*Transforms int to string*/
void intToString(int, char *);

/* Prints string with format */
void printf(const char *, ...);

/* Clears the screen, displaying an empty screen */
void clear_screen();

/*Draws pixel*/
void draw_pixel(int, int);

/* Deletes the last character from stdin */
void backspace();

#endif
