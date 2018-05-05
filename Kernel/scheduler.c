#include <scheduler.h>
#include <string.h>
#include <video_driver.h>
#include <heap.h>

int currentProcessId = 0; //esto es para tener constancia de los PID de cada programa
int smallestSlotFree = 0; //este numero es para manejar cuando un proceso termina, ese slot queda libre y seguro es el mas chico en la tabla
int allProcess = 0;

ProcessSlot * tableProcess;

void createProcess(void * entryPoint, char * nameProcess){
	Process newProcess;
	newProcess.PID = currentProcessId++;
	memcpy(newProcess.processName,nameProcess,20);
	newProcess.heap = NULL;
	newProcess.status = RUNNING;
	addProcess(newProcess);
}

/* NO FUNCA
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
} */

void addProcess(Process newProcess){
	//ProcessSlot * newSlot = createSlot(newProcess);
	ProcessSlot * newSlot = (ProcessSlot *) allocPage();
	newSlot->process = newProcess;

	if(tableProcess == NULL){
		tableProcess = newSlot;
		newSlot->next = NULL;
	} else {
		ProcessSlot * aux = tableProcess;
		while(aux->next != NULL){
			aux->process.status = FINISHED;
			aux = aux->next;
		}

		aux->next = newSlot;
		aux->process.status = FINISHED;
		newSlot->next = NULL;
	}

	allProcess++;
	smallestSlotFree++;
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

Process getCurrentProcess(){
	return tableProcess->process;
}