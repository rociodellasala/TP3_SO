#include <scheduler.h>
#include <string.h>
#include <video_driver.h>
#include <heap.h>
#include <converter.h>
#include <memoryManager.h>
#include <interrupts.h>

#define QUANTUM 5

static int numberOfTicks = 0;
int currentProcessId = 0; //esto es para tener constancia de los PID de cada programa
int allProcess = 0;
ProcessSlot * currentProcess;
ProcessSlot * lastProcess;
ProcessSlot * tableProcess;

static void * kernelStack;

void * switchUserToKernel(void * esp){
	currentProcess->process.userStack = esp;
	return kernelStack;
}

void * switchKernelToUser(){
	return currentProcess->process.userStack;
}

void initializeKernelStack() {
	kernelStack = (void *) allocPage();
}

void runScheduler(){
	if(currentProcess == NULL) //Si todavia no hay ningun proceso en la cola de procesos
		return;

	/* Check quantum */
	if(numberOfTicks < QUANTUM) {
		numberOfTicks++;
		return;
	}
	
	/*print_string("CurrentProcess: ");
	print_string(currentProcess->process.processName);
	print_string(" - siguiente: ");
	print_string(currentProcess->next->process.processName);
	print_string(" - lastProcess: ");
	print_string(lastProcess->process.processName);
	nextLine();
	print_string("Todos los procesos: ");
	nextLine();
	printAllCurrentProcess();
	nextLine();
	*/

	/* Run next process */
	numberOfTicks = 0;

	if(currentProcess->process.status == RUNNING){ 
		currentProcess->process.status = READY;
	}

	currentProcess = currentProcess->next;
	currentProcess->process.status = RUNNING;
	//print_string("cambiando de proceso a: ");
	//print_string(currentProcess->process.processName);
	//printAllCurrentProcess();
}

void startProcess(void * entryPoint, char * nameProcess){
	createProcess(entryPoint, nameProcess);
	currentProcess->process.status = RUNNING;
	enableTickInter();
	((EntryPoint)currentProcess->process.startingPoint)();
}

ProcessSlot * createSlot(Process newProcess){
	ProcessSlot newSlotStruct;
	ProcessSlot * newSlot;
	newSlotStruct.process = newProcess;
	newSlotStruct.next = NULL;
	newSlot = &newSlotStruct;
	int sizeNewProcessSlotStruct = sizeof(ProcessSlot);
	void * destination = findAvaiableHeapKernelPage(sizeNewProcessSlotStruct);
	newSlot = memcpy(destination, newSlot, sizeNewProcessSlotStruct);
	return newSlot;
}

int createProcess(void * entryPoint, char * nameProcess){
	Process newProcess;
	newProcess.PID = currentProcessId++;
	memcpy(newProcess.processName,nameProcess,20); //deberia ser strlen de nameProcess
	newProcess.heap = NULL;
	newProcess.status = READY;
	newProcess.startingPoint = entryPoint;
	newProcess.pipe = NULL;
	//newProcess.baseStack = allocPage();
	newProcess.userStack = fillStackFrame(entryPoint, 0x1000);
	addProcessToPCB(newProcess);
	return newProcess.PID;
}

void addProcessToPCB(Process newProcess){
	ProcessSlot * newSlot = createSlot(newProcess);
	
	if(tableProcess == NULL){
		tableProcess = currentProcess = lastProcess = newSlot;
		currentProcess->next = currentProcess; 
	} else {
		ProcessSlot * aux = lastProcess;
		aux->next = lastProcess = newSlot;
		lastProcess->next = tableProcess;
	}

	allProcess++;
}

void printAllCurrentProcess(){
	ProcessSlot * aux = tableProcess;
	int i = 0;
	print_string(" ---------- TABLE PROCESS ---------- \n");
	
	while(aux != NULL && i < allProcess){
		print_string("Process name: ");
		print_string(aux->process.processName);
		print_string("  -  PID: ");
		print_int(aux->process.PID);
		if(aux->process.heap == NULL)
			print_string("	-  Heap: No heap avaiable");
		else
			print_string("	-  Heap: There is a heap");
		print_string("  -  Status: ");
		if((aux->process.status) == 1) 
			print_string("RUNNING");
		else if((aux->process.status) == 2)
			print_string("READY");
		else
			print_string("FINISHED");
		nextLine();
		i++;
		aux = aux->next;
	}
}

ProcessSlot * searchRunningProcess(){
	ProcessSlot * aux = tableProcess;

	while(aux != NULL && aux->process.status != RUNNING){
		aux = aux->next;
	}

	return aux;
}

void terminateProcess(int PID){
	ProcessSlot * aux = tableProcess;

	if(tableProcess->process.PID == PID){
		releasePage(tableProcess->process);
		tableProcess = tableProcess->next;
		return;
	}

	ProcessSlot * previous = tableProcess;
	aux = tableProcess->next;

	while(aux->process.PID != PID && aux != NULL){
		previous = aux;
		aux = aux->next;
	}

	//Deberia manejarse el caso que haya terminado y aux == NULL
	releasePage(aux->process);
	previous->next = aux->next;
	return;
}

int getCurrentPid(){
	return currentProcess->process.PID;
}

ProcessSlot * getProcessFromPid(int pid){
	ProcessSlot * aux = tableProcess;

	while(aux != NULL && aux->process.PID != pid){
		aux = aux->next;
	}

	return aux;
}

void removeFinishedProcess() {

	if(tableProcess->process.status == FINISHED){
		//releasePage(tableProcess->process.userStack);
		releasePage(tableProcess->process);
		tableProcess = tableProcess->next;
		lastProcess->next = tableProcess;
		return;
	}

	ProcessSlot * aux = tableProcess->next;
	ProcessSlot * prev = tableProcess;
	
	while(aux != tableProcess){
		if(aux->process.status == FINISHED) {

			// Remove process 
			//releasePage(aux->process.userStack);
			releasePage(aux->process);
			prev->next = aux->next;
			return;

		}

		prev = aux;
		aux = aux->next;
	}
}


void removeProcess(int pid){
	print_string("CurrentProcess: ");
	print_string(currentProcess->process.processName);
	print_string(" - siguiente: ");
	print_string(currentProcess->next->process.processName);
	print_string(" - lastProcess: ");
	print_string(lastProcess->process.processName);
	print_string(" - first: ");
	print_string(tableProcess->process.processName);
	nextLine();
	print_string("Todos los procesos: ");
	nextLine();
	printAllCurrentProcess();
	nextLine();

	ProcessSlot * slot = getProcessFromPid(pid);
	slot->process.status = FINISHED;
	
	removeFinishedProcess();
	
	if(lastProcess == currentProcess){
		lastProcess = currentProcess->next;
	}

	currentProcess = currentProcess->next;
	


	currentProcess->process.status = RUNNING;
	currentProcess->next = currentProcess->next->next;
	allProcess--;
	print_string("CurrentProcess: ");
	print_string(currentProcess->process.processName);
	print_string(" - siguiente: ");
	print_string(currentProcess->next->process.processName);
	print_string(" - lastProcess: ");
	print_string(lastProcess->process.processName);
	print_string(" - first: ");
	print_string(tableProcess->process.processName);
	nextLine();
	print_string("Todos los procesos: ");
	nextLine();
	printAllCurrentProcess();
	nextLine();
	enableTickInter();

	print_string("Restaurando SHELL - Presione ENTER");
	
	restoreContext();
	
	print_string("Restaurando SHELL - Presione ENTER2");
}

void * fillStackFrame(void * entryPoint, void * baseStack) {
	StackFrame * frame = (StackFrame*)baseStack - 1;
	frame->gs =	0x001;
	frame->fs =	0x002;
	frame->r15 = 0x003;
	frame->r14 = 0x004;
	frame->r13 = 0x005;
	frame->r12 = 0x006;
	frame->r11 = 0x007;
	frame->r10 = 0x008;
	frame->r9 =	 0x009;
	frame->r8 =	 0x00A;
	frame->rsi = 0x00B;
	frame->rdi = 0x00C;
	frame->rbp = 0x00D;
	frame->rdx = 0x00E;
	frame->rcx = 0x00F;
	frame->rbx = 0x010;
	frame->rax = 0x011;
	frame->rip = (qword)entryPoint;
	frame->cs =	 0x008;
	frame->eflags = 0x202;
	frame->rsp = (qword)&(frame->base);
	frame->ss = 0x000;
	frame->base = 0x000;

	return (void *) frame;	
}

//falta ahcerse


void blockProgram(){
	return;
}