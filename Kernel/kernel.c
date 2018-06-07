#include "heap.h"
#include "interrupts.h"
#include "lib.h"
#include "memoryManager.h"
#include "moduleLoader.h"
#include "scheduler.h"
#include "systemcalls.h"
#include "video_driver.h"
#include "mutex.h"

extern byte bss;
extern byte endOfKernelBinary;
extern byte endOfKernel;

static const qword PageSize = 0x1000;

void * kernelStack;

static void * shell = (void *) 0x600000;
static void * linearGraph = (void *) 0x800000;
static void * parabolicGraph = (void *) 0x900000;
static void * processRead = (void *) 0xA00000;
static void * testMemoryManager = (void *) 0xB00000;
static void * processWrite = (void *) 0xC00000;
static void * background = (void *) 0xD00000;
static void * processReadAndWrite = (void *) 0xE00000;
static void * processWriteAndRead = (void *) 0xF00000;
static void * producer = (void *) 0xF10000;
static void * consumer = (void *) 0xF20000;
static void * multithread = (void *) 0xF30000;
static void * proA = (void *) 0xF40000;
static void * proB = (void *) 0xF50000;
static void * proC = (void *) 0xF60000;
static void * threadTest = (void *) 0xF70000;
static void * bubbleSort = (void *) 0xF80000;

void clearBSS(void * bssAddress, qword bssSize){
	memset(bssAddress, 0, bssSize);
}

void * getStackBase(){
	return (void *)(
		(qword)&endOfKernel
		+ PageSize * 8		  	/* The size of the stack itself, 32KiB */
		- sizeof(qword)			/* Begin at the top of the stack */
	);
}

void * initializeKernelBinary(){
	void * moduleAddresses[17];
	moduleAddresses[0] = shell;
	moduleAddresses[1] = linearGraph; 
	moduleAddresses[2] = parabolicGraph;
	moduleAddresses[3] = processRead; 
	moduleAddresses[4] = testMemoryManager;
	moduleAddresses[5] = processWrite;
	moduleAddresses[6] = background; 
	moduleAddresses[7] = processReadAndWrite; 
	moduleAddresses[8] = processWriteAndRead; 
	moduleAddresses[9] = producer; 
	moduleAddresses[10] = consumer; 
	moduleAddresses[11] = multithread;
	moduleAddresses[12] = proA;
	moduleAddresses[13] = proB; 
	moduleAddresses[14] = proC; 
	moduleAddresses[15] = threadTest;
	moduleAddresses[16] = bubbleSort;
	loadModules(&endOfKernelBinary, moduleAddresses);
	clearBSS(&bss, &endOfKernel - &bss);
	return getStackBase();
}

void initializeKernelStack(){
	kernelStack = (void *) allocPage(PAGE_SIZE * 2,"Kernel stack");
}

void initializeKernelMemory(){
	allocPage(20 * PAGE_SIZE,"Kernel space");
}

void reserveMemoryForMemoryManager(){
	allocPage(sizeof(memoryManager),"Memory Manager");
}

int main(){
	_cli();		
	load_idt();
	load_systemcalls();
	start_video_mode();
	_sti();

	initializeMemoryManager();
	initializeKernelMemory();
	initializeKernelStack();
	reserveMemoryForMemoryManager();
	initializeKernelHeap();
	initiliazeMutexes();
	startProcess(shell, "shell");
	return 0;
}
