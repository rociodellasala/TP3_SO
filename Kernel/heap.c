#include "heap.h"
#include "structs.h"
#include "heap.h"
#include "string.h"
#include "memoryManager.h"
#include "scheduler.h"
#include "process.h"
#include "video_driver.h"
#include "converter.h"
#include "lib.h"

extern ProcessSlot * tableProcess;
kernelHeapHeader kernelHeader;

void initializeKernelHeap(){
	int i;
	
	kernelHeader.nextPage = 0;
	
	for(i = 0; i < PAGES_KERNEL_HEAP; i++){
		kernelHeapPage heapPageK;
		heapPageK.occupiedBytes = 0;
		heapPageK.freeBytes = PAGE_SIZE;
		heapPageK.pageAddress = allocPage();
		kernelHeader.kernelHeapPages[i] = heapPageK;
	}
}

void printKernelHeap(){
	int i;
	
	for(i = 0; i < PAGES_KERNEL_HEAP; i++){
		print_string("Pagina ");
		print_int(i);
		print_string(" del heap kernel: ");
		printHex((qword) kernelHeader.kernelHeapPages[i].pageAddress);
		nextLine();
	}
}

p_heapPage createHeapPage(){
	int sizeNewHeapStruct;
	void * kernelHeapPage;
	heapPage newHeap;
	p_heapPage newHeapPointer;

	newHeap.currentPage = allocPage();
	newHeap.occupiedBytes = 0;
	newHeap.nextHeapPage = NULL;
	newHeap.freeBytes = PAGE_SIZE;
	newHeapPointer = &newHeap;
	
	sizeNewHeapStruct = sizeof(heapPage);
	kernelHeapPage = findAvaiableHeapKernelPage(sizeNewHeapStruct);
	newHeapPointer = memcpy(kernelHeapPage, newHeapPointer, sizeNewHeapStruct);
	return newHeapPointer;
}

void * findAvaiableHeapKernelPage(int size){
	int nextPage = kernelHeader.nextPage;
	kernelHeapPage heapPageK = kernelHeader.kernelHeapPages[nextPage];
	
	if(heapPageK.freeBytes >= size){
		void * address = (heapPageK.pageAddress) + (heapPageK.occupiedBytes);
		kernelHeader.kernelHeapPages[nextPage].occupiedBytes += size;
		kernelHeader.kernelHeapPages[nextPage].freeBytes -= size;
		return address;
	} else {
		heapPageK = kernelHeader.kernelHeapPages[nextPage + 1];
		kernelHeader.nextPage++;
		kernelHeader.kernelHeapPages[nextPage + 1].occupiedBytes += size;
		kernelHeader.kernelHeapPages[nextPage + 1].freeBytes -= size;
		return heapPageK.pageAddress;
	}
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
	if(firstPage == NULL){
		firstPage = createHeapPage();
		ProcessSlot * currentProcessSlot = searchRunningProcess();
		currentProcessSlot->process.heap = firstPage;
		return firstPage;
	}
	
	if(firstPage->freeBytes >= size){
		return firstPage;
	}
	
	p_heapPage currentHeapPage = firstPage->nextHeapPage;
	p_heapPage previousPage = firstPage;

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
