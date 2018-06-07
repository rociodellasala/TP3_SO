#include "ascii_keyboard.h"
#include "keyboard_driver.h"
#include "types.h"

#define BUFFER_SIZE 2000 /* 2000 = 80 * 25 */

static byte buffer[BUFFER_SIZE];
static int index = 0; 
static int bufferIndex = 0; 

static boolean ctrlPressed = false; 
static boolean bloqMayusPressed = false; 
static boolean shiftRPressed = false; 
static boolean shiftLPressed = false; 
static boolean altPressed = false; 

extern int allProcess;
 
extern byte read_keyboard();

void keyboardHandler() {
	byte key = read_keyboard();	
	checkKeyPressed(key);
}

void checkKeyPressed(unsigned char key){
	checkSpecialKeyPressed(key);
    
	if(key & 0X80)
	    return;
	
   	if(ctrlPressed || altPressed)
   		return;
    
    	getCharacterFromKeyboard(&key);
	updateBuffer(key);
}

void checkSpecialKeyPressed(unsigned char key){
	if (key == 0x1D || key == 0X9D) 
		ctrlPressed = !ctrlPressed; 
	else if(key == 0x36 || key == 0xB6)
		shiftRPressed =  !shiftRPressed;
   	else if(key == 0x2A || key == 0XAA)
		shiftLPressed = !shiftLPressed;
   	else if(key == 0x38 || key == 0xB8)
		altPressed = !altPressed;
    	else if(key == 0x3A)
		bloqMayusPressed = !bloqMayusPressed;
}

void getCharacterFromKeyboard(unsigned char * key){
	if(!bloqMayusPressed && !shiftLPressed && !shiftRPressed){
		*key = KEY_VALUE[*key];
   	} else {
		if(bloqMayusPressed && !shiftLPressed && !shiftRPressed){
			*key=KEY_VALUE[*key];
			if(*key >= 'a'&& *key <= 'z'){
				*key = *key - 'a' + 'A';
			}
		} else {	
			if((shiftLPressed || shiftRPressed) && !bloqMayusPressed){
				*key = SHIFT_KEY_VALUE[*key];
			} else {
				unsigned char aux = KEY_VALUE[*key];
				if(aux < 'a' || aux > 'z')
					*key = SHIFT_KEY_VALUE[*key];
				else 
					*key = KEY_VALUE[*key];
			}
		}
	}
}

void updateBuffer(unsigned char key){
	buffer[bufferIndex] = key;
	bufferIndex = (bufferIndex + 1) % BUFFER_SIZE;
}

unsigned char getBuffer(){
	if(index != bufferIndex){
		byte aux = buffer[index];
		index = (index +  1) % BUFFER_SIZE;
		return aux;
	}

	return EOF;
}

void readBuffer(unsigned char * buff, int size){
	int i = 0;
	unsigned char c;

	while (i < size - 1 && (c = getBuffer()) != EOF) {
		buff[i] = (unsigned char) c;
		i++;
	}

	buff[i] = 0;
}


