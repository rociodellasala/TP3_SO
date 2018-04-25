#ifndef KEYBOARD_DRIVER_H
#define KEYBOARD_DRIVER_H

/* Reads keyboard and updates buffer */
void keyboard_handler();

/* Determines which key was pressed and if it's printable adds it to buffer */
void update_buffer(unsigned char key);

/* Returns last character that was saved on buffer */
char get_buffer();

/* Reads what was saved on buffer */
void read_buffer(char * buff, int size);

#endif
