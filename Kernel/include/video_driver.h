#ifndef VSA_DRIVER_H
#define VSA_DRIVER_H

#include "types.h"

/* Starts video mode and initializes pointers  */
void  start_video_mode();

/* Deletes a line */
void deleteLine(int);

/* Puts pixel in the received coordinates */
void draw_pixel(int, int);

/* Draws a char in the x and y coordinates */
void draw_char(unsigned char, int, int);

/* Draws string in the indicated coordinates */
void draw_string(char *, int, int);

/* Draws a filled rectangle from two points, the lower left and the upper right */
void draw_filled_rectangle(int, int, int, int, int);

/* Blackens the screen and resets the writing position */
void clear_screen();

/* Writes a character in the next writing position */
void print_char(unsigned char);

/* Prints string in the next writing position */
void print_string(const char *);

/* Prints string until the indicated length */
void print_string_by_length(const char *, int);

/* Deletes the character in the previous writing position */
void delete();

/* Ends the line and continue drawing characters in the bottom line */
void nextLine();

/* Changes current font color acording to parameter */
void changeFontColor(int);

/* When the text reaches the bottom, it moves all the characters one line up */
void move_screen();

/* Prints number in the next writing position */
void print_int(qword);

/* Returns the number of digits in an int */
int countDigits(qword);

/* SACARRRRRRRRR */
void printc(unsigned char);
void prints(const char *);
void printi(qword);

#endif
