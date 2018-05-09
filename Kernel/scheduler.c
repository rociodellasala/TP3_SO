#include "interrupts.h"
#include "memoryManager.h"
#include "process.h"
#include "scheduler.h"
#include "string.h"
#include "time.h"
#include "video_driver.h"

#define QUANTUM 5
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
	currentProcess->process.userStack = esp;
	return kernelStack;
}

void * switchKernelToUser(){
	return currentProcess->process.userStack;
}

void runScheduler(){
	if(currentProcess->process.PID == 0 && allProcess > 1 && allProcessForeground > 0)
		currentProcess->process.status = LOCKED;

	if(currentProcess == NULL) 
		return;

	if(numberOfTicks < QUANTUM) {
		numberOfTicks++;
		return;
	}
	
	numberOfTicks = 0;

	if(currentProcess->process.status == RUNNING)
		currentProcess->process.status = READY;
	
	currentProcess = currentProcess->next;
	
	while(currentProcess->process.status != READY)
		currentProcess = currentProcess->next;
	
	currentProcess->process.status = RUNNING;
	/* DESPUES ELIMINAR ESTO */
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
			if(lastProcess == aux)
				lastProcess = prev;
			
			releasePage(aux->process);
			prev->next = aux->next;
			return;
		}
		prev = aux;
		aux = aux->next;
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
	if(pid == 0){
		exitMessage();
		currentProcess = lastProcess = tableProcess = NULL;
		return;
	}

	/* DESPUES ELIMINAR ESTO */
	prints("\nA eliminar: ");
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
	nextLine();
	
	ProcessSlot * slot = getProcessFromPid(pid);
	
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

	/* DESPUES ELIMINAR ESTO */
	prints("\n---------- DESPUES DE ELIMINAR ----------");
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
	nextLine();
	
	enableTickInter();
	if(slot->process.foreground == FOREGROUND)
	print_string("Restaurando SHELL - Presione ENTER");
	
	restoreContext();
}


//falta hacer una funcion que desbloqueee!!
void blockProcess(int pid){
	ProcessSlot * p = getProcessFromPid(pid);
	p->process.status = LOCKED;
	return;
}
