#include <interrupts.h>
#include <keyboard_driver.h>
#include <moduleLoader.h>
#include <stdint.h>
#include <string.h>
#include <systemcalls.h>
#include <video_driver.h>
#include <converter.h>

extern byte bss;
extern byte data;
extern byte rodata;
extern byte text;
extern byte endOfKernelBinary;
extern byte endOfKernel;

static const qword PageSize = 0x1000;

extern unsigned int read();

static void * shell = (void *)0x400000;
static void * linearGraph = (void *)0x700000;
static void * parabolicGraph = (void *)0x900000;

static int pageByte;

void * map(void * fisica, void * module){
	memcpy(fisica,module,8192);
	return fisica;
	//print_string("asd");
	//printHex(module);
	//*((uint64_t *)entry) = fisica;
}

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
			shell = map((void *)0x6000,shell);
			((EntryPoint)shell)();
			break;

		case '2':
			linearGraph = map((void *)0x8000,linearGraph);
			//printHex(linearGraph);
			((EntryPoint)linearGraph)();
			break;

		case '3':
			parabolicGraph = map((void *)0xA000,parabolicGraph);
			((EntryPoint)parabolicGraph)();
			break;
	}
}

void start(){
	while(1){
		//clear_screen();
		//print_menu();
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
