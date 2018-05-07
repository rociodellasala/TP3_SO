#include <stdint.h>
#include <string.h>
#include <keyboard_driver.h>
#include <moduleLoader.h>
#include <video_driver.h>
#include <interrupts.h>
#include <systemcalls.h>
#include <scheduler.h>
#include <converter.h>
#include <heap.h>
#include <memoryManager.h>
#include <lib.h>
#include <scheduler.h>

extern byte bss;
extern byte data;
extern byte rodata;
extern byte text;
extern byte endOfKernelBinary;
extern byte endOfKernel;

static const qword PageSize = 0x1000;

extern unsigned int read();

static void * shell = (void *)0x600000;
static void * linearGraph = (void *)0x900000;
static void * parabolicGraph = (void *)0xB00000;
static void * needMemory = (void *)0xD00000;
static void * testMemoryManager = (void *)0xE00000;

void * map(void * fisica, void * module){
	memcpy(fisica,module,8192);
	return fisica;
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
	void * moduleAddresses[] = {shell, linearGraph, parabolicGraph,needMemory,testMemoryManager,};
	loadModules(&endOfKernelBinary, moduleAddresses);
	clearBSS(&bss, &endOfKernel - &bss);
	return getStackBase();
}

int main(){
	_cli();		
	load_idt();
	load_systemcalls();
	start_video_mode();
	_sti();
	initializeMemoryManager();
	initializeKernelHeap();
	initializeKernelStack();
	//printKernelHeap();
	startProcess(shell, "shell");

	while(1);

	return 0;
}
