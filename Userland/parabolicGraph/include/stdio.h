#ifndef STDIO_H
#define STDIO_H

#include "types.h"

/* Prints character */
void putchar(unsigned char);

char getchar();

/*Returns string length*/
int strlen(const char *);

/*Transforms int to string*/
void intostr(int, char *);

/* Prints string with format */
void printf(const char *, ...);

/* Clears the screen, displaying an empty screen */
void clear_screen();

/*Draws pixel*/
void draw_pixel(int, int);

/* Deletes the last character from stdin */
void backspace();

/* Reads a string as an int */
char * readInt(char *, int *);

/* Reads until the end of line */
char* readLine();

/* Returns true if the character is a number */
int isNum(char );

/* Draws the x-axis and y-axis */
void coordinates();

/* Reads a number */
int getNum(int *);

#endif
