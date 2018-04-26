#ifndef KEYBOARD_DRIVER_H
#define KEYBOARD_DRIVER_H

/* Reads keyboard and updates buffer */
void keyboard_handler();

/* Determines which key was pressed */
void checkKeyPressed(unsigned char key);

/* Determines if a special key was pressed like BloqMayus or Shift */
void checkSpecialKeyPressed(unsigned char key);

/* Gets the correct ASCII from keyborad according to the key code */
void getCharacterFromKeyboard(unsigned char * key);

/* Adds character to buffer if it's printable */
void update_buffer(unsigned char key);

/* Returns last character that was saved on buffer */
char get_buffer();

/* Reads what was saved on buffer */
void read_buffer(char * buff, int size);

#endif
