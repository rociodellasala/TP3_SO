#include "converter.h"
#include "heap.h"
#include "lib.h"
#include "memoryManager.h"
#include "scheduler.h"
#include "structs.h"
#include "video_driver.h"
#include "mutex.h"
#include "process.h"

extern ProcessSlot * tableProcess;

kernelHeapHeader * kernelHeader;

void initializeKernelHeap(){
	int heapSize = sizeof(kernelHeapHeader);
	int i;
	kernelHeader = allocPage(heapSize);
	
	for(i = 0; i < MAX_FREE; i++){
		kernelHeader->lastProcessSlotFree[i] = INVALID_LAST_FREE_SLOT;
		kernelHeader->lastPipeSlotFree[i] = INVALID_LAST_FREE_SLOT;
		kernelHeader->lastHeapSlotFree[i] = INVALID_LAST_FREE_SLOT;
	}

	kernelHeader->lastProcessSlot = 0;
	kernelHeader->lastMutexSlot = 0;
	kernelHeader->lastPipeSlot = 0;
	kernelHeader->lastHeapSlot = 0;


	return;
}


/*Funcion de debuggeo, no prestarle atencion*/
void printHeaderInfo(){
	int i;
	nextLine();
	nextLine();
	nextLine();
	print_string("Procesos: ");
	nextLine();
	nextLine();
	for(i = 0; i < kernelHeader->lastProcessSlot; i++){
		print_string("Process: ");
		print_string(kernelHeader->allProcessSlots[i].process.processName);
		print_string("	PID: ");
		print_int(kernelHeader->allProcessSlots[i].process.PID);
		nextLine();
	}
	print_string("Slots de procesos libres: ");
	nextLine();
	for(i = 0; i < MAX_FREE; i++){
		if(kernelHeader->lastProcessSlotFree[i] != INVALID_LAST_FREE_SLOT){
			print_string("Index liberado: ");
			print_int(kernelHeader->lastProcessSlotFree[i]);
			print_string("	en posicion: ");
			print_int(i);
			nextLine();
		}
	}
	nextLine();
	print_string("Pipes: ");
	nextLine();
	nextLine();
	for(i = 0; i < kernelHeader->lastPipeSlot; i++){
		print_string("Process PID creator: ");
		print_int(kernelHeader->allPipesSlots[i].processOnePID);
		nextLine();
		print_string("Process expected: ");
		print_string(kernelHeader->allPipesSlots[i].processTwoName);
		nextLine();
	}
	print_string("Slots de pipes libres: ");
	nextLine();
	for(i = 0; i < MAX_FREE; i++){
		if(kernelHeader->lastPipeSlotFree[i] != INVALID_LAST_FREE_SLOT){
			print_string("Index liberado: ");
			print_int(kernelHeader->lastPipeSlotFree[i]);
			print_string("	en posicion: ");
			print_int(i);
			nextLine();
		}
	}
	nextLine();
	print_string("User heap's: ");
	nextLine();
	nextLine();
	print_string("Slots de heaps libres: ");
	nextLine();
	for(i = 0; i < MAX_FREE; i++){
		if(kernelHeader->lastHeapSlotFree[i] != INVALID_LAST_FREE_SLOT){
			print_string("Index liberado: ");
			print_int(kernelHeader->lastHeapSlotFree[i]);
			print_string("	en posicion: ");
			print_int(i);
			nextLine();
		}
	}
}


p_heapPage createHeapPage(){
	int sizeNewHeapStruct;
	void * kernelHeapPage;
	s_heapPage newHeap;
	p_heapPage newHeapPointer;

	newHeap.currentPage = allocPage(PAGE_SIZE);
	newHeap.occupiedBytes = 0;
	newHeap.nextHeapPage = NULL;
	newHeap.freeBytes = PAGE_SIZE;
	newHeapPointer = &newHeap;
	sizeNewHeapStruct = sizeof(s_heapPage);
	kernelHeapPage = findAvaiableHeapKernelPage(sizeNewHeapStruct);
	newHeapPointer = memcpy(kernelHeapPage, newHeapPointer, sizeNewHeapStruct);
	return newHeapPointer;
}

void * findAvaiableHeapKernelPage(int size){
	void * pointerToReturn;
	int sizeProcesSlot = sizeof(ProcessSlot);
	int sizePipe = sizeof(s_pipe);
	int sizeMutex = sizeof(s_mutex);
	if(size == sizeProcesSlot){
		if(kernelHeader->lastProcessSlotFree[0] == INVALID_LAST_FREE_SLOT)
			return (void *) &kernelHeader->allProcessSlots[kernelHeader->lastProcessSlot++];
		else{
			pointerToReturn = (void *) &kernelHeader->allProcessSlots[kernelHeader->lastProcessSlotFree[0]];
			moveFreeArray(kernelHeader->lastProcessSlotFree);
			return pointerToReturn;
			}
	}else if(size == sizePipe){
		if(kernelHeader->lastPipeSlotFree[0] == INVALID_LAST_FREE_SLOT)
			return (void *) &kernelHeader->allPipesSlots[kernelHeader->lastPipeSlot++];
		else{
			pointerToReturn = (void *) &kernelHeader->allPipesSlots[kernelHeader->lastPipeSlotFree[0]];
			moveFreeArray(kernelHeader->lastPipeSlotFree);
			return pointerToReturn;
		}
	}else if(size == sizeMutex){
			return (void *) &kernelHeader->allMutex[kernelHeader->lastMutexSlot++];
	}else{
		if(kernelHeader->lastHeapSlotFree[0] == INVALID_LAST_FREE_SLOT){
			return (void *) &kernelHeader->allHeapSlots[kernelHeader->lastHeapSlot++];
		}
		else{
			pointerToReturn = (void *) &kernelHeader->allHeapSlots[kernelHeader->lastHeapSlotFree[0]];
			moveFreeArray(kernelHeader->lastHeapSlotFree);
			return pointerToReturn;
		}	
	}	
}

void moveFreeArray(int * freeArray){
	int i;

	for(i = 0; i < MAX_FREE - 1; i++){
		freeArray[i] = freeArray[i+1];
	}
	freeArray[i] = INVALID_LAST_FREE_SLOT;
}

void releaseStructs(ProcessSlot * slot){
	releaseProcessHeap(slot);
	releasePipeSlot(slot);
	releaseProcessSlot(slot);
}

void releaseProcessSlot(ProcessSlot * slot){
	int i;
	int indexFree;

	for(i = 0; i < MAX_PROCESS_SLOT; i++){
		if(&kernelHeader->allProcessSlots[i] == slot){
			indexFree = i;
			break;
		}
	}

	for(i = 0; i < MAX_FREE; i++){
		if(kernelHeader->lastProcessSlotFree[i] == INVALID_LAST_FREE_SLOT){
			kernelHeader->lastProcessSlotFree[i] = indexFree;
			break;
		}
	}
}

void releaseProcessHeap(ProcessSlot * slot){
	p_heapPage currentHeapPage = slot->process.heap;

	while(currentHeapPage != NULL){
		releaseHeapStruct(currentHeapPage);
		currentHeapPage = currentHeapPage->nextHeapPage;
	}

}

void releaseHeapStruct(p_heapPage heap){
	int i;
	int indexFree;

	for(i = 0; i < MAX_HEAP_SLOT * MAX_PROCESS_SLOT; i++){
		if(heap == &kernelHeader->allHeapSlots[i]){
			indexFree = i;
			break;
		}
	}

	for(i = 0; i < MAX_FREE; i++){
		if(kernelHeader->lastHeapSlotFree[i] == INVALID_LAST_FREE_SLOT){
			kernelHeader->lastHeapSlotFree[i] = indexFree;
			break;
		}
	}
}

void releasePipeSlot(ProcessSlot * slot){
	int i;

	for(i = 0; i < slot->process.pipeIndex; i++){
		releasePipeStruct(slot->process.pipes[i]);
	}
}

void releasePipeStruct(p_pipe pipe){
	ProcessSlot * connectingProcess = getProcessFromPid(pipe->processTwoPID);
	ProcessSlot * callingProcess = getProcessFromPid(pipe->processOnePID);
	int i;
	int indexFree;



	if(callingProcess != NULL && connectingProcess != NULL)
		return;

	for(i = 0; i < MAX_PIPES * MAX_PROCESS_SLOT; i++){
		if(pipe == &kernelHeader->allPipesSlots[i]){
			indexFree = i;
			break;
		}
	}
	for(i = 0; i < MAX_FREE; i++){
		if(kernelHeader->lastPipeSlotFree[i] == INVALID_LAST_FREE_SLOT){
			kernelHeader->lastPipeSlotFree[i] = indexFree;
			break;
		}
	}

	freeMutex(pipe->mutex);

}


void * malloc_heap(int size){
	ProcessSlot * currentProcessSlot = searchRunningProcess();
	p_heapPage heap = findAvaiableHeapPage(currentProcessSlot->process.heap, size);
	void * freePointer = findFreePointer(heap);
	heap->freeBytes -= size;
	heap->occupiedBytes += size;
	return freePointer;
}	

p_heapPage findAvaiableHeapPage(p_heapPage firstPage, int size){
	ProcessSlot * currentProcessSlot;
	p_heapPage currentHeapPage, previousPage;

	if(firstPage == NULL){
		firstPage = createHeapPage();
		currentProcessSlot = searchRunningProcess();
		currentProcessSlot->process.heap = firstPage;
		return firstPage;
	}
	
	if(firstPage->freeBytes >= size){
		return firstPage;
	}
	
	currentHeapPage = firstPage->nextHeapPage;
	previousPage = firstPage;

	while(currentHeapPage != NULL && currentHeapPage->freeBytes < size){
		previousPage = currentHeapPage;
		currentHeapPage = currentHeapPage->nextHeapPage;
	}

	if(currentHeapPage == NULL){
		previousPage->nextHeapPage = createHeapPage();
		return previousPage->nextHeapPage;
	} else 
		return currentHeapPage;
}

void * findFreePointer(p_heapPage heapPage){
	int occupied = heapPage->occupiedBytes;
	void * startingAddress = heapPage->currentPage;
	return startingAddress + occupied;
}
