#include <scheduler.h>
#include <string.h>
#include <video_driver.h>

int currentProcessId = 0; //esto es para tener constancia de los PID de cada programa
int smallestSlotFree = 0; //este numero es para manejar cuando un proceso termina, ese slot queda libre y seguro es el mas chico en la tabla
int allProcess = 0;

Process tableProcess[PROCESS_SLOTS];

void createProcess(void * entryPoint, char * nameProcess){
	Process newProcess;
	newProcess.PID = currentProcessId++;
	memcpy(newProcess.processName,nameProcess,20);
	newProcess.heap = NULL;
	addProcess(newProcess);
}

void addProcess(Process newProcess){
	tableProcess[smallestSlotFree] = newProcess;
	allProcess++;
	smallestSlotFree++;
}

void printAllCurrentProcess(){
	int i;
	for(i = 0 ; i < allProcess; i++){
		print_string("Process name: ");
		print_string(tableProcess[i].processName);
		print_string("	PID: ");
		print_int(tableProcess[i].PID);
		if(tableProcess[i].heap == NULL)
			print_string("	No heap avaiable");
		else
			print_string("	There is a heap");
		nextLine();
	}
}

Process getCurrentProcess(){
	return tableProcess[0];
}