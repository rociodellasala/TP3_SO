#ifndef KEYBOARD_DRIVER_H
#define KEYBOARD_DRIVER_H

/* Reads keyboard and updates buffer */
void keyboardHandler();

/* Determines which key was pressed */
void checkKeyPressed(unsigned char);

/* Determines if a special key was pressed like BloqMayus or Shift */
void checkSpecialKeyPressed(unsigned char);

/* Gets the correct ASCII from keyborad according to the key code */
void getCharacterFromKeyboard(unsigned char *);

/* Adds character to buffer if it's printable */
void updateBuffer(unsigned char);

/* Returns last character that was saved on buffer */
unsigned char getBuffer();

/* Reads what was saved on buffer */
void readBuffer(unsigned char *, int);

#endif
