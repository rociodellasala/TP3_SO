#include "interrupts.h"
#include "heap.h"
#include "lib.h"
#include "memoryManager.h"
#include "process.h"
#include "scheduler.h"
#include "stack.h"
#include "string.h"
#include "video_driver.h"

int currentProcessId = 0; 
int allProcess = 0;

extern int allProcessBackground;
extern int allProcessForeground;

extern ProcessSlot * currentProcess;

ProcessSlot * lastProcess;
ProcessSlot * tableProcess;

ProcessSlot * createSlot(Process newProcess){
	ProcessSlot newSlotStruct;
	ProcessSlot * newSlot;
	int sizeNewProcessSlotStruct;	
	void * destination;

	newSlotStruct.process = newProcess;
	newSlotStruct.next = NULL;
	newSlot = &newSlotStruct;
	sizeNewProcessSlotStruct = sizeof(ProcessSlot);
	destination = findAvaiableHeapKernelPage(sizeNewProcessSlotStruct);
	newSlot = memcpy(destination, newSlot, sizeNewProcessSlotStruct);
	return newSlot;
}

int checkIfForegroundOrBackground(char * nameProcess){
	if(strcmp(nameProcess,"shell")){
		return FOREGROUND;
	} else {
		char c = charAtPos(nameProcess,strlen(nameProcess)-1);
		
		if(c == '&'){
			allProcessForeground++;
			return FOREGROUND;
		} else {
			allProcessBackground++;
			return BACKGROUND;
		}
	}
}

int createProcess(void * entryPoint, char * nameProcess){
	int i;
	Process newProcess;
	newProcess.PID = currentProcessId++;
	newProcess.heap = NULL;
	newProcess.status = READY;
	newProcess.foreground = checkIfForegroundOrBackground(nameProcess);
	
	if(newProcess.foreground == BACKGROUND || strcmp(nameProcess,"shell"))
		strcpy(newProcess.processName,nameProcess);
	else
		strncpy(newProcess.processName,nameProcess,strlen(nameProcess) - 1);
	
	for(i = 0; i < MAX_PIPES; i++)
		newProcess.pipes[i] = NULL;

	newProcess.pipeIndex = 0;
	
	newProcess.threadSize = 1;
	newProcess.threads = newProcess.currentThread = createThread(entryPoint);
	
	addProcessToPCB(newProcess);
	return newProcess.PID;
}


ThreadSlot * createThreadSlot(Thread thread){
	ThreadSlot newThreadSlotStruct;
	ThreadSlot * newThreadSlot;
	int sizeNewThreadSlotStruct;	
	void * destination;

	newThreadSlotStruct.thread = thread;
	newThreadSlotStruct.next = NULL;
	newThreadSlot = &newThreadSlotStruct;
	sizeNewThreadSlotStruct = sizeof(ThreadSlot);
	destination = findAvaiableHeapKernelPage(sizeNewThreadSlotStruct);
	newThreadSlot = memcpy(destination, newThreadSlot, sizeNewThreadSlotStruct);
	return newThreadSlot;
}

ThreadSlot * createThread(void * entryPoint){
	Thread thread;
	thread.baseStack = allocPage(PAGE_SIZE);
	thread.userStack = fillStackFrame(entryPoint, thread.baseStack);
	thread.startingPoint = entryPoint;
	thread.status = READY;

	ThreadSlot * threadSlot = createThreadSlot(thread);
	return threadSlot;
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
			print_string(" -  Heap: No heap avaiable");
		else
			print_string("  -  Heap: There is a heap");
		print_string(" -  Status: ");
		
		if((aux->process.status) == RUNNING) 
			print_string("RUNNING");
		else if((aux->process.status) == READY)
			print_string("READY");
		else if((aux->process.status) == LOCKED)
			print_string("LOCKED");
		else
			print_string("FINISHED");
		if((aux->process.foreground) == FOREGROUND)
		print_string("  -  FOREGROUND ");
		else if((aux->process.foreground) == BACKGROUND)
		print_string("  -  BACKGROUND");
		nextLine();
		
		i++;
		aux = aux->next;

	}
}

int getProcessFromName(char * procesName){
	ProcessSlot * aux = tableProcess;

	while(aux != NULL && ! strcmp(aux->process.processName,procesName)){
		aux = aux->next;
		if(aux == tableProcess)
			break;
	}
	
	if(! strcmp(aux->process.processName,procesName)){
		return -1;
	}

	return aux->process.PID;
}

ProcessSlot * getProcessFromPid(int pid){
	ProcessSlot * aux = tableProcess;

	if(pid == -1)
		return NULL;

	while(aux != NULL && aux->process.PID != pid){
		aux = aux->next;
		if(aux == tableProcess)
			break;
	}

	if(aux->process.PID != pid)
		return NULL;

	return aux;
}
