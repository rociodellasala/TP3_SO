#include <scheduler.h>
#include <string.h>
#include <video_driver.h>
#include <heap.h>
#include <converter.h>
#include <memoryManager.h>

int currentProcessId = 0; //esto es para tener constancia de los PID de cada programa
int allProcess = 0;

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
	newProcess.status = RUNNING;
	addProcess(newProcess);
	return newProcess.PID;
}

void addProcess(Process newProcess){
	//ProcessSlot * newSlot = createSlot(newProcess);
	ProcessSlot * newSlot = createSlot(newProcess);
	if(tableProcess == NULL){
		tableProcess = newSlot;
		print_string("La tabla de procesos era NULL");
		printHex(newSlot);
		nextLine();
	} else {
		ProcessSlot * aux = tableProcess;
		while(aux->next != NULL){
			aux->process.status = FINISHED;
			aux = aux->next;
		}
		print_string("La tabla de procesos no era NULL");
		printHex(newSlot);
		nextLine();
		aux->next = newSlot;
		aux->process.status = FINISHED;
		//printHex(newSlot->next);
		newSlot->next = NULL;
	}
	allProcess++;
}

void printAllCurrentProcess(){
	ProcessSlot * aux = tableProcess;

	while(aux != NULL){
		print_string("Process name: ");
		print_string(aux->process.processName);
		print_string("	PID: ");
		print_int(aux->process.PID);
		if(aux->process.heap == NULL)
			print_string("	No heap avaiable");
		else
			print_string("	There is a heap");
		print_string("  Status: ");
		print_int(aux->process.status);
		nextLine();
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
