#include "interrupts.h"
#include "memoryManager.h"
#include "process.h"
#include "scheduler.h"
#include "string.h"
#include "heap.h"
#include "time.h"
#include "video_driver.h"
#include "mutex.h"

#define QUANTUM 10
#define THREADQUANTUM 3
#define WAIT 60000000

static int numberOfTicks = 0;

extern int currentProcessId; 
extern int allProcess;
int allProcessBackground = 0;
int allProcessForeground = 0;

ProcessSlot * currentProcess;
extern ProcessSlot * lastProcess;
extern ProcessSlot * tableProcess;

extern void * kernelStack;

void * switchUserToKernel(void * esp){
	currentProcess->process.currentThread->thread.userStack = esp;
	return kernelStack;
}

void * switchKernelToUser(){
	return currentProcess->process.currentThread->thread.userStack;
}

void runScheduler(){
	if(currentProcess->process.PID == 0 && allProcess > 1 && allProcessForeground > 0){
		currentProcess->process.status = LOCKED;
	}

	if(currentProcess == NULL) 
		return;

	if(numberOfTicks < QUANTUM) {
			
		numberOfTicks++;
		disableTickInter();
		checkIfThreadChange();
		enableTickInter();
		return;
	}
	
	
	numberOfTicks = 0;


	if(currentProcess->process.status == RUNNING){
		currentProcess->process.status = READY;
	}

	currentProcess = currentProcess->next;

	while(currentProcess->process.status != READY){
		currentProcess = currentProcess->next;
	}
	
	currentProcess->process.status = RUNNING;
}

void startProcess(void * entryPoint, char * nameProcess){
	createProcess(entryPoint, nameProcess);
	currentProcess->process.status = RUNNING;
	currentProcess->process.currentThread->thread.status = RUNNING;
	enableTickInter();
	((EntryPoint)currentProcess->process.currentThread->thread.startingPoint)();
}

ProcessSlot * searchRunningProcess(){
	ProcessSlot * aux = tableProcess;

	while(aux != NULL && aux->process.status != RUNNING)
		aux = aux->next;
	
	return aux;
}


int getCurrentPid(){
	return currentProcess->process.PID;
}

void removeFinishedProcess() {
	ProcessSlot * aux;
	ProcessSlot * prev;

	if(tableProcess->process.status == FINISHED){
		releasePage(tableProcess->process);
		tableProcess = tableProcess->next;
		lastProcess->next = tableProcess;
		return;
	}

	aux = tableProcess->next;
	prev = tableProcess;
	while(aux != tableProcess){
		if(aux->process.status == FINISHED) {
			if(lastProcess == aux)
				lastProcess = prev;
			changeProcessTree(aux->process);
			releasePage(aux->process);
			releaseStructs(aux);
			prev->next = aux->next;
			return;
		}
		prev = aux;
		aux = aux->next;
	}
}

void changeProcessTree(Process process){
	int i;int j;
	ProcessSlot * father = getProcessFromPid(process.fatherPID);

	for(i = 0; i < MAX_CHILDS; i++){
		if(process.childsPID[i] != INVALID_PROCESS_PID)
			addChild(process.childsPID[i],getProcessFromPid(0));
	}

	for(j = 0; j < MAX_CHILDS; j++){
		if(father->process.childsPID[j] == process.PID){
			father->process.childsPID[j] = INVALID_PROCESS_PID;
		}
	}

}

void exitMessage(){
	int i = 0, j = 3;
	clear_screen();
	print_string("Leaving OS in... ");
		
	while(i < WAIT){
		if(i == WAIT/6 || i == WAIT/4 || i == WAIT/2 ){
			print_int(j);
			print_string(" ");
			j--;
		}
		i++;
	}

	clear_screen();
}


void removeProcess(int pid){
	ProcessSlot * slot;

	if(pid == 0){
		exitMessage();
		currentProcess = lastProcess = tableProcess = NULL;
		while(1);
		return;
	}
	
	slot = getProcessFromPid(pid);
	
	if(slot->process.foreground == FOREGROUND)
		allProcessForeground--;
	else
		allProcessBackground--;

	slot->process.status = FINISHED;
	allProcess--;
	removeFinishedProcess();

	if(allProcessForeground == 0 && tableProcess->process.status == LOCKED)
		tableProcess->process.status = READY;
	
	currentProcess = currentProcess->next;
	currentProcess->process.status = RUNNING;

	enableTickInter();
	if(slot->process.foreground == FOREGROUND)
	print_string("Restoring SHELL - Press ENTER to continue");
	
	
	restoreContext();
}

int removeProcessFromTerminal(int pid){
	ProcessSlot * slot;

	slot = getProcessFromPid(pid);
	if(pid == 0){
		exitMessage();
		currentProcess = lastProcess = tableProcess = NULL;
		while(1);
		return -1;
	}

	if(slot == NULL){
		return -1;
	} 

	
	
	if(slot->process.foreground == FOREGROUND)
		allProcessForeground--;
	else
		allProcessBackground--;
	
	slot->process.status = FINISHED;
	allProcess--;
	removeFinishedProcess();
	enableTickInter();
	return 1;
}

void blockProcess(int pid){
	ProcessSlot * p = getProcessFromPid(pid);
	if(p != NULL){
		p->process.status = LOCKED;
		numberOfTicks = QUANTUM;
	}
	return;
}

void unblockProcess(int pid){
	ProcessSlot * p = getProcessFromPid(pid);
	if(p != NULL)
		p->process.status = READY;
	return;
}

Thread blockThread(Thread thread){
	thread.status = LOCKED;
	thread.threadQuantum = 0;
	return thread;
}

Process deleteThreadFromProcess(Process process){
	ThreadSlot * thread = process.threads;
	ThreadSlot * prev;

	while(thread->thread.TID != process.currentThread->thread.TID){
		prev = thread;
		thread = thread->next;
	}
	
	prev->next = thread->next;
	
	process.threadSize--;
	
	if(process.threadSize == 1 && process.threads->thread.status == LOCKED){
		process.threads->thread.status = READY;
	}

	return process;
}

void checkIfThreadChange(){
	if(currentProcess->process.currentThread->thread.threadQuantum < THREADQUANTUM){
		currentProcess->process.currentThread->thread.threadQuantum++;
		return;
	}
	
	currentProcess->process.currentThread->thread.threadQuantum = 0;
	nextThread();
}


void nextThread() {
	if(currentProcess->process.currentThread->thread.status == RUNNING) {
		currentProcess->process.currentThread->thread.status = READY;
	}
	
	if(currentProcess->process.currentThread->next == NULL){
		
		currentProcess->process.currentThread = currentProcess->process.threads;
		
		if(currentProcess->process.currentThread->thread.status == READY){
			currentProcess->process.currentThread->thread.status = RUNNING;
			return;
		}
	}
		
	while(currentProcess->process.currentThread->next->thread.status != READY) {
		currentProcess->process.currentThread = currentProcess->process.currentThread->next;	
	}

	currentProcess->process.currentThread = currentProcess->process.currentThread->next;
	currentProcess->process.currentThread->thread.status = RUNNING;

}

void sleep(int segs){
	int i;
	int j;

	disableTickInter();
	for(i = 0; i < 6000 * segs; i++)
		for(j = 0; j < 6000 * segs; j++);

	enableTickInter();
}
