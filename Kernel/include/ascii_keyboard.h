#ifndef _ASCII_CODE
#define _ASCII_CODE

/* Define the position of the keys on keyboard */
const char KEY_VALUE[] = { 0, '|', '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '\'', '¿', '\b', 			/* 0 - 14 */
			'\t', 'q', 'w', 'e', 'r', 't','y', 'u', 'i', 'o', 'p', '´', '+', '\n',				/* 15 - 28 */
			/*CAPS*/ 0, 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', 0, '{', '}', 				/* 29 - 41 */
			/*LSHIFT*/  0, '<', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '-', /*RSHIFT*/ 0, 		/* 42 - 54 */
			/*CTRL*/ 0, /*ALT*/  0,  ' ', /*ALT*/ 0, /*CTRL*/ 0 , 0,   0,   0,   0,   0,   0,   0,   0,
    0,	/* < ... F10 */
    0,	/* 69 - Num lock*/
    0,	/* Scroll Lock */
    0,	/* Home key */
    0,	/* Up Arrow */
    0,	/* Page Up */
  '-',
    0,	/* Left Arrow */
    0,
    0,	/* Right Arrow */
  '+',
    0,	/* 79 - End key*/
    0,	/* Down Arrow */
    0,	/* Page Down */
    0,	/* Insert Key */
    0,	/* Delete Key */
    0,   0,   0,
    0,	/* F11 Key */
    0,	/* F12 Key */
    0,	/* All other keys are undefined */
};  						/* 55 - 59 */

/* Define the position of the keys when SHIFT key is pressed on keyboard */
const char SHIFT_KEY_VALUE[] = { 0, '°', '!', '"', '#', '$', '%', '&', '/', '(', ')', '=', '?', '¡', '\b',	  	/* 0 - 14 */
			'\t', 'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', '¨', '*', '\n',	   	 		/* 15 - 28 */
			/*CAPS*/ 0, 'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', 0, '[', ']', 				/* 29 - 41 */
			/*LSHIFT*/ 0, '>', 'Z', 'X', 'C', 'V', 'B', 'N', 'M', ';', ':', '_', 0,  			/* 42 - 54 */
			/*CTRL*/ 0, /*LALT*/ 0, ' '};  									/* 55 - 59 */


#endif
