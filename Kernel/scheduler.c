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
int allProcessBackground = 0;
int allProcessForeground = 0;
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
	
	if(currentProcess->process.PID == 0 && allProcess > 1 && allProcessForeground > 0){
		currentProcess->process.status = LOCKED;
	}


	if(currentProcess == NULL) //Si todavia no hay ningun proceso en la cola de procesos
		return;

	/* Check quantum */
	if(numberOfTicks < QUANTUM) {
		numberOfTicks++;
		return;
	}
	
	
	/*prints("CurrentProcess: ");
	printi(currentProcess->process.PID);
	prints(" - siguiente: ");
	printi(currentProcess->next->process.PID);
	prints(" - lastProcess: ");
	printi(lastProcess->process.PID);
	nextLine();
	prints("Todos los procesos: ");
	printi(allProcess);
	nextLine();
	printAllCurrentProcess();
	nextLine();*/
	

	/* Run next process */
	numberOfTicks = 0;

	if(currentProcess->process.status == RUNNING){ 
		currentProcess->process.status = READY;
	}

	currentProcess = currentProcess->next;

	while(currentProcess->process.status != READY){
		currentProcess = currentProcess->next;
	}

	
	currentProcess->process.status = RUNNING;
	//prints("          Cambiando de proceso : ");
	//prints(currentProcess->process.processName);
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
	if(strcmp(nameProcess,"shell")){
		newProcess.foreground = FOREGROUND;
	} else {
	char c = charAtPos(nameProcess,strlen(nameProcess)-1);
	if(c == '&'){
		newProcess.foreground = FOREGROUND;
		allProcessForeground++;
	} else {
		newProcess.foreground = BACKGROUND;
		allProcessBackground++;
	}}
	newProcess.startingPoint = entryPoint;
	newProcess.pipe = NULL;
	newProcess.baseStack = allocPage();
	newProcess.userStack = fillStackFrame(entryPoint, newProcess.baseStack);
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
	prints(" ---------- TABLE PROCESS ---------- \n");
	
	while(aux != NULL && i < allProcess){
		prints("Process name: ");
		prints(aux->process.processName);
		prints("  -  PID: ");
		printi(aux->process.PID);
		if(aux->process.heap == NULL)
			prints("	-  Heap: No heap avaiable");
		else
			prints("	-  Heap: There is a heap");
		prints("  -  Status: ");
		if((aux->process.status) == RUNNING) 
			prints("RUNNING");
		else if((aux->process.status) == READY)
			prints("READY");
		else if((aux->process.status) == LOCKED)
			prints("LOCKED");
		else
			prints("FINISHED");
		if((aux->process.foreground) == FOREGROUND)
		prints("  -  FOREGROUND ");
		else if((aux->process.foreground) == BACKGROUND)
		prints("  -  BACKGROUND");
		nextLine();
		prints(" - NEXT PID: ");
		i++;
		aux = aux->next;
		printi(aux->process.PID);
	}
}

ProcessSlot * searchRunningProcess(){
	ProcessSlot * aux = tableProcess;

	while(aux != NULL && aux->process.status != RUNNING){
		aux = aux->next;
	}

	return aux;
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
			releasePage(aux->process);
			prev->next = aux->next;
			return;

		}

		prev = aux;
		aux = aux->next;
	}
}


void removeProcess(int pid){
	if(pid == 0){
		clear_screen();
		print_string("Leaving OS in... ");
		int i = 0, j = 3;
		while(i < 400000000){
			if(i == 100000000 || i == 200000000 || i == 300000000){
				print_int(j);
				print_string(" ");
				j--;
			}
			i++;
		}
		clear_screen();
		currentProcess = lastProcess = tableProcess = NULL;
		return;
	}
	/*prints("A eliminar: ");
	printi(pid);
	prints("\n---------- ANTES DE ELIMINAR ----------");
	prints("\nCurrentProcess: ");
	prints(currentProcess->process.processName);
	printi(currentProcess->process.PID);
	prints(" - siguiente: ");
	prints(currentProcess->next->process.processName);
	printi(currentProcess->next->process.PID);
	prints(" - lastProcess: ");
	prints(lastProcess->process.processName);
	printi(lastProcess->process.PID);
	prints(" - first: ");
	prints(tableProcess->process.processName);
	nextLine();
	prints("Todos los procesos: ");
	nextLine();
	printAllCurrentProcess();
	nextLine();*/

	ProcessSlot * slot = getProcessFromPid(pid);
	if(slot->process.foreground == FOREGROUND)
		allProcessForeground--;
	else
		allProcessBackground--;
	slot->process.status = FINISHED;
	allProcess--;
	removeFinishedProcess();
	
	/*prints("\nCurrentProcess: ");
	prints(currentProcess->process.processName);
	printi(currentProcess->process.PID);
	prints(" - siguiente: ");
	prints(currentProcess->next->process.processName);
	printi(currentProcess->next->process.PID);
	prints(" - lastProcess: ");
	prints(lastProcess->process.processName);
	printi(lastProcess->process.PID);
	prints(" - first: ");
	prints(tableProcess->process.processName);
	nextLine();
	prints("Todos los procesos: ");
	nextLine();
	printAllCurrentProcess();
	nextLine();*/

	if(lastProcess == currentProcess){
		lastProcess = currentProcess->next;
	}

	if(allProcessForeground == 0 && tableProcess->process.status == LOCKED){
		tableProcess->process.status = READY;
	}

	currentProcess = currentProcess->next;
	


	currentProcess->process.status = RUNNING;

	/*prints("\nCurrentProcess: ");
	prints(currentProcess->process.processName);
	printi(currentProcess->process.PID);
	prints(" - siguiente: ");
	prints(currentProcess->next->process.processName);
	printi(currentProcess->next->process.PID);
	prints(" - lastProcess: ");
	prints(lastProcess->process.processName);
	printi(lastProcess->process.PID);
	prints(" - first: ");
	prints(tableProcess->process.processName);
	nextLine();
	prints("Todos los procesos: ");
	nextLine();
	printAllCurrentProcess();
	nextLine();*/
	
	enableTickInter();
	if(slot->process.foreground == FOREGROUND)
	print_string("Restaurando SHELL - Presione ENTER");
	
	restoreContext();

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

//falta hacer una funcion que desbloqueee!!


void blockProgram(int pid){
	ProcessSlot * p = getProcessFromPid(pid);
	p->process.status = LOCKED;
	return;
}