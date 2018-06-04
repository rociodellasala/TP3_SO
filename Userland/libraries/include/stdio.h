#ifndef STDIO_H
#define STDIO_H

#define MAX_SIZE 2000
#define exit 2

/* Prints string with format */
void printf(const char *, ...);

void printfColor(int color, const char *, ...);

/* Call system call to draw pixel in console */
void draw_pixel(int x, int y);

/* Prints character */
void putchar(unsigned char);

void putcharColor(int color, unsigned char);

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

/* Gets an int from stdin */
int getNum(int *);

/* Sleeps program for some segs */
void sleep(int segs);

#endif
