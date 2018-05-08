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
		//prints(" - NEXT PID: ");
		i++;
		aux = aux->next;
		//printi(aux->process.PID);
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