#include "mutex.h"
#include "scheduler.h"
#include "structs.h"
#include "lib.h"
#include "string.h"
#include "heap.h"

extern kernelHeapHeader * kernelHeader;

void initiliazeMutexes(){
	int i;

	for(i = 0; i < MAX_MUTEX_SLOT; i++){
		createMutex();
	}
}

p_mutex createMutex(){
	s_mutex mutexStruct;
	p_mutex mutexPointer;
	void * destination;
	int mutexStructSize;
	int i;

	mutexStruct.mutexValue = true;
	mutexStruct.avaiable = true;
	for(i = 0; i < MAX_QUEUED_PROCESS; i++){
		mutexStruct.pidQueueWait[i] = INVALID_PROCESS;
		mutexStruct.pidQueueSignal[i] = INVALID_PROCESS;
	}
	mutexPointer = &mutexStruct;
	mutexStructSize = sizeof(s_mutex);
	destination = findAvaiableHeapKernelPage(mutexStructSize);
	mutexPointer = memcpy(destination, mutexPointer, mutexStructSize);

	return mutexPointer;
}

int getFreeMutex(char * mutexName){
	int i;
	p_mutex mutex;
	for(i = 0; i < MAX_MUTEX_SLOT; i++){
		mutex = &kernelHeader->allMutex[i];
		if(mutex->avaiable == true)
			break;
	}
	if(i == MAX_MUTEX_SLOT)
		return -1;

	mutex->avaiable = false;
	strcpy(mutex->idName,mutexName);
	return i;
}

int getMutexByName(char * mutexName){
	int i;
	
	for(i = 0; i < MAX_MUTEX_SLOT; i++){
		if(strcmp(kernelHeader->allMutex[i].idName,mutexName))
			break;
	}

	if(i == MAX_MUTEX_SLOT)
		return INVALID_INDEX;
	else
		return i;
}

void freeMutex(int index){
	int i;

	if(index >= MAX_QUEUED_PROCESS)
		return;

	p_mutex mutex = &kernelHeader->allMutex[index];
	mutex->avaiable = true;
	mutex->mutexValue = true;

	for(i = 0; i < MAX_QUEUED_PROCESS; i++){
		mutex->pidQueueWait[i] = INVALID_PROCESS;
		mutex->pidQueueSignal[i] = INVALID_PROCESS;
	}
	return;
}

/*

void wait(int index){
	p_mutex mutex = allMutex[index];
	int nextPid;

	if(mutex->mutexValue == false){
		addToQueue(mutex->pidQueue);
		do{
			blockProcess(getCurrentPid());
			nextPid = mutex->pidQueue[0];
		}while(nextPid != getCurrentPid() || mutex->mutexValue != true);
		removeFromQueue(mutex->pidQueue);
	}
	

	mutex->mutexValue = false;
}

*/

int wait(int index){
	p_mutex mutex = &kernelHeader->allMutex[index];

	if(mutex->mutexValue == true){
		mutex->mutexValue = false;
		return SUCCESFUL;
	}

	if(mutex->mutexValue == false){
		if(isInQueue(mutex->pidQueueWait)){
			blockProcess(getCurrentPid());
		}else{
			addToQueue(mutex->pidQueueWait);
			blockProcess(getCurrentPid());
		}
		return LOCK;
	}else if(mutex->pidQueueWait[0] == getCurrentPid()){
		removeFromQueue(mutex->pidQueueWait);
		mutex->mutexValue = false;
		return SUCCESFUL;
	}else{
		blockProcess(getCurrentPid());
		return LOCK;
	}
}

/*

void signal(int index){
	p_mutex mutex = allMutex[index];
	int nextPid;

	if(mutex->mutexValue == true){
		addToQueue(mutex->pidQueue);
		do{
			print_string("Bloquenado programa");
			nextLine();
			blockProcess(getCurrentPid());
			nextPid = mutex->pidQueue[0];
		}while(nextPid != getCurrentPid() || mutex->mutexValue != false);
		removeFromQueue(mutex->pidQueue);
	}
	mutex->mutexValue = true;
}
*/

int signal(int index){
	p_mutex mutex = &kernelHeader->allMutex[index];

	if(mutex->mutexValue == false){
		mutex->mutexValue = true;
		return SUCCESFUL;
	}

	if(mutex->mutexValue == true){
		if(isInQueue(mutex->pidQueueSignal)){
			blockProcess(getCurrentPid());
		}else{
			addToQueue(mutex->pidQueueSignal);
			blockProcess(getCurrentPid());
		}
		return LOCK;
	}else if(mutex->pidQueueSignal[0] == getCurrentPid()){
		removeFromQueue(mutex->pidQueueSignal);
		mutex->mutexValue = true;
		return SUCCESFUL;
	}else{
		blockProcess(getCurrentPid());
		return LOCK;
	}
}

void addToQueue(int * queue){
	int i;

	for(i = 0; i < MAX_QUEUED_PROCESS; i++){
		if(queue[i] != INVALID_PROCESS){
			queue[i] = getCurrentPid();
			break;
		}
	}
}

void removeFromQueue(int * queue){
	int i;

	for(i = 0; i < MAX_QUEUED_PROCESS - 1; i++){
		queue[i] = queue[i + 1];
	}
}

boolean isInQueue(int * queue){
	int i;

	for(i = 0; i < MAX_QUEUED_PROCESS - 1; i++){
		if(queue[i] == getCurrentPid())
			return true;
	}

	return false;
}