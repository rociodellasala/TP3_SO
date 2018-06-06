#include "interrupts.h"
#include "heap.h"
#include "lib.h"
#include "memoryManager.h"
#include "process.h"
#include "scheduler.h"
#include "stack.h"
#include "string.h"
#include "video_driver.h"
#include "converter.h"

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
	int i;int j;
	Process newProcess;
	newProcess.PID = currentProcessId++;
	newProcess.heap = NULL;
	newProcess.status = READY;
	newProcess.foreground = checkIfForegroundOrBackground(nameProcess);

	if(! strcmp(nameProcess,"shell"))
		newProcess.fatherPID = getCurrentPid();
	else
		newProcess.fatherPID = INVALID_PROCESS_PID;

	addChild(newProcess.PID,getProcessFromPid(getCurrentPid()));

	for(j = 0; j < MAX_CHILDS; j++)
		newProcess.childsPID[j] = INVALID_PROCESS_PID;
	
	if(newProcess.foreground == BACKGROUND || strcmp(nameProcess,"shell"))
		strcpy(newProcess.processName,nameProcess);
	else
		strncpy(newProcess.processName,nameProcess,strlen(nameProcess) - 1);
	
	for(i = 0; i < MAX_PIPES; i++)
		newProcess.pipes[i] = NULL;

	newProcess.pipeIndex = 0;
	newProcess.stdin = NULL;
	newProcess.stdout = NULL;
	
	newProcess.threadSize = 1;
	newProcess.threads = newProcess.currentThread = createThread(entryPoint, newProcess.threadSize,newProcess.processName,newProcess.PID);
	
	addProcessToPCB(newProcess);
	return newProcess.PID;
}

void addChild(int childPID, ProcessSlot * slot){
	int i;

	for(i = 0; i < MAX_CHILDS; i++){
		if(slot->process.childsPID[i] == INVALID_PROCESS_PID){
			slot->process.childsPID[i] = childPID;
			break;
		}
	}
}

ThreadSlot * createThreadSlot(Thread newThread){
	ThreadSlot newThreadSlotStruct;
	ThreadSlot * newThreadSlot;
	int sizeNewThreadSlotStruct;	
	void * destination;
	
	newThreadSlotStruct.thread = newThread;
	newThreadSlotStruct.next = NULL;
	newThreadSlot = &newThreadSlotStruct;
	sizeNewThreadSlotStruct = sizeof(ThreadSlot);
	destination = findAvaiableHeapKernelPage(sizeNewThreadSlotStruct);
	newThreadSlot = memcpy(destination, newThreadSlot, sizeNewThreadSlotStruct);

	return newThreadSlot;
}

ThreadSlot * createThread(void * entryPoint, int threadSize,char * nameProcess,int processPID){
	Thread thread;	
	char information[60] = {0};
	getNodeInfo(information,nameProcess,processPID,"Stack of ");	
	thread.TID = threadSize;
	thread.status = READY;
	thread.threadQuantum = 0;
	thread.baseStack = allocPage(PAGE_SIZE,information);
	thread.userStack = fillStackFrame(entryPoint, thread.baseStack);
	thread.startingPoint = entryPoint;
	
	return createThreadSlot(thread);
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
			print_string("  -  Heap: No heap avaiable");
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

void printProcessTree(ProcessSlot * currentSlot, int lines){
	int i;int j;
	nextLine();
	for(i = 0; i < lines; i++)
		print_stringColor(" ","white");
	print_stringColor(currentSlot->process.processName,"white");
	print_stringColor(": ","white");

	for(j = 0; j < MAX_CHILDS; j++){
		if(currentSlot->process.childsPID[j] != INVALID_PROCESS_PID){
			ProcessSlot * aux = getProcessFromPid(currentSlot->process.childsPID[j]);
			printProcessTree(aux, lines + 8);
		}
	}
	
}

int getProcessFromName(char * procesName){
	ProcessSlot * aux = tableProcess;

	while(aux != NULL && ! strcmp(aux->process.processName,procesName)){
		aux = aux->next;
		if(aux == tableProcess)
			break;
	}
	
	if(aux == NULL || ! strcmp(aux->process.processName,procesName)){
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

	if(aux == NULL || aux->process.PID != pid)
		return NULL;

	return aux;
}

char * getProcessNameFromPid(int pid){
	ProcessSlot * slot = getProcessFromPid(pid);
	return slot->process.processName;
}

ThreadSlot * getLastThreadFromProcess(Process auxProcess){
	ThreadSlot * auxThread = auxProcess.threads;

	while(auxThread->next != NULL){
		auxThread = auxThread->next;
	}

	return auxThread;
}

Process addThreadToProcess(int pid, void * exec){
	ThreadSlot * newThread, * lastThreadProcess;

	ProcessSlot * aux = getProcessFromPid(pid);	
	Process process = aux->process;

	process.threadSize++;
	newThread = createThread(exec, process.threadSize,process.processName,process.PID);
	lastThreadProcess = getLastThreadFromProcess(process);

	lastThreadProcess->next = newThread;
	return process;
}

