#ifndef VSA_DRIVER_H
#define VSA_DRIVER_H

#include <types.h>

/* Starts video mode. Initializes pointers.  */
void  start_video_mode();

/* Deletes a line */
void deleteLine(int line);

/* Puts pixel in the received coordinates */
void draw_pixel(int x, int y);

/* Draws a char in the x and y coordinates */
void draw_char(unsigned char c, int x, int y);

/* Draws string in the indicated coordinates */
void draw_string( char * str , int x , int y);

/* Draws a filled rectangle from two points, the lower left and the upper right. */
void draw_filled_rectangle(int x1, int y1, int x2, int y2, int color);

/*  Blackens the screen and resets the writing position */
void clear_screen();

/* Writes a character in the next writing position. */
void print_char(unsigned char c);

/* Prints string in the next writing position */
void print_string(const char * str);

/* Prints string until the indicated length */
void print_string_by_length(const char * str, int length);

/* Deletes the character in the previous writing position */
void delete();

/* Ends the line and continue drawing characters in the bottom line */
void nextLine();

/* Changes current font color acording to parameter */
void changeFontColor(int color);

/* When the text reaches the bottom, it moves all the characters one line up */
void move_screen();

/* Prints number in the next writing position */
void print_int(qword n);

/* Returns the number of digits in an int */
int countDigits(qword n);

/* Displays main menu*/
void print_menu();

#endif
