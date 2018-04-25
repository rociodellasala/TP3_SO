/* _loader.c */
#include <stdint.h>

extern char bss;
extern char endOfBinary;

int main();

void * memset(void * destiny, int32_t c, uint64_t length);

int _start(){
	//Clean BSS
	memset(&bss, 0, &endOfBinary - &bss);

	return main();

}

void * memset(void * destination, int32_t c, uint64_t length){
	uint8_t chr = (uint8_t)c;
	char * dst = (char *)destination;

	while(length--)
		dst[length] = chr;

	return destination;
}
