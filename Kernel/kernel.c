#include <interrupts.h>
#include <keyboard_driver.h>
#include <moduleLoader.h>
#include <stdint.h>
#include <string.h>
#include <systemcalls.h>
#include <video_driver.h>

extern byte bss;
extern byte data;
extern byte rodata;
extern byte text;
extern byte endOfKernelBinary;
extern byte endOfKernel;

static const qword PageSize = 0x1000;

extern unsigned int read();

static void * const shell = (void *)0x400000;
static void * const linearGraph = (void *)0x700000;
static void * const parabolicGraph = (void *)0x900000;

typedef int (*EntryPoint)();

void clearBSS(void * bssAddress, qword bssSize) {
	memset(bssAddress, 0, bssSize);
}

void * getStackBase() {
	return (void *)(
		(qword)&endOfKernel
		+ PageSize * 8		  	/* The size of the stack itself, 32KiB */
		- sizeof(qword)			/* Begin at the top of the stack */
	);
}

void * initializeKernelBinary() {
	void * moduleAddresses[] = {shell, linearGraph, parabolicGraph,};
	loadModules(&endOfKernelBinary, moduleAddresses);
	clearBSS(&bss, &endOfKernel - &bss);
	return getStackBase();
}

void readFromBuff(){
	int i = 0;
	char opcion = '0';

	while((opcion = get_buffer()) == EOF || i < 1){
		i++;
	}

	switch(opcion){
		case '1':
			((EntryPoint)shell)();
			break;

		case '2':
			((EntryPoint)linearGraph)();
			break;

		case '3':
			((EntryPoint)parabolicGraph)();
			break;
	}
}

void start(){
	while(1){
		clear_screen();
		print_menu();
		readFromBuff();
	}
}

int main(){
	_cli();		
	load_idt();
	load_systemcalls();
	start_video_mode();
	_sti();
	
	start();

	return 0;
}
