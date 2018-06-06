#include "mutex.h"
#include "scheduler.h"
#include "structs.h"
#include "lib.h"
#include "string.h"
#include "heap.h"
#include "video_driver.h"

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
	p_mutex mutex = &kernelHeader->allMutex[index];
	
	if(index >= MAX_QUEUED_PROCESS)
		return;

	mutex->avaiable = true;
	mutex->mutexValue = true;

	for(i = 0; i < MAX_QUEUED_PROCESS; i++){
		mutex->pidQueueWait[i] = INVALID_PROCESS;
		mutex->pidQueueSignal[i] = INVALID_PROCESS;
	}
	return;
}

int wait(int index){
	p_mutex mutex = &kernelHeader->allMutex[index];

	if(mutex->mutexValue == true){
		if(mutex->pidQueueWait[0] == getCurrentPid() || mutex->pidQueueWait[0] == INVALID_INDEX){
			mutex->mutexValue = false;
			removeFromQueue(mutex->pidQueueWait);
			unblockProcess(mutex->pidQueueSignal[0]);
			return SUCCESFUL;
		}else{
			if(isInQueue(mutex->pidQueueWait)){
				blockProcess(getCurrentPid());
			}else{
				addToQueue(mutex->pidQueueWait);
				blockProcess(getCurrentPid());
			}
		return LOCK;
		}
	}

	if(mutex->mutexValue == false){
		if(isInQueue(mutex->pidQueueWait)){
			blockProcess(getCurrentPid());
		}else{
			addToQueue(mutex->pidQueueWait);
			blockProcess(getCurrentPid());
		}
		return LOCK;
	}
	return LOCK;
}

int signal(int index){
	p_mutex mutex = &kernelHeader->allMutex[index];

	if(mutex->mutexValue == false){
		if(mutex->pidQueueSignal[0] == getCurrentPid() || mutex->pidQueueSignal[0] == INVALID_INDEX){
			mutex->mutexValue = true;
			removeFromQueue(mutex->pidQueueSignal);
			unblockProcess(mutex->pidQueueWait[0]);
			return SUCCESFUL;
		}else{
			if(isInQueue(mutex->pidQueueSignal)){
				blockProcess(getCurrentPid());
			}else{
				addToQueue(mutex->pidQueueSignal);
				blockProcess(getCurrentPid());
			}
		return LOCK;
		}
	}
	else if(mutex->mutexValue == true){
		if(isInQueue(mutex->pidQueueSignal)){
			blockProcess(getCurrentPid());
		}else{
			addToQueue(mutex->pidQueueSignal);
			blockProcess(getCurrentPid());
		}
		return LOCK;
	}

	return LOCK;
}

void addToQueue(int * queue){
	int i;

	for(i = 0; i < MAX_QUEUED_PROCESS; i++){
		if(queue[i] == INVALID_PROCESS){
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

	queue[i] = INVALID_PROCESS;
}

boolean isInQueue(int * queue){
	int i;

	for(i = 0; i < MAX_QUEUED_PROCESS; i++){
		if(queue[i] == getCurrentPid())
			return true;
	}

	return false;
}

void printQueue(int * queue, char * type){
	int i;
	print_stringColor("Queue ","white");
	print_stringColor(type,"white");
	print_stringColor(": ","white");
	for(i = 0; i < MAX_QUEUED_PROCESS; i++){
		if(queue[i] > 0){
			print_intColor(queue[i],"white");
			print_stringColor(" ","white");
		}
		else{
			print_stringColor(" - ","white");
			print_intColor(queue[i] * -1,"white");
		}

	}

	nextLineAnyway();
}