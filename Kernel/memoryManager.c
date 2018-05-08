#include <memoryManager.h>
#include <string.h>
#include <video_driver.h>
#include <converter.h>
#include <structs.h>

struct memoryPage memoryPages[PAGEQUANTITY];
struct memoryFreeStack freePages;

void initializeMemoryManager(){
	splitMemory(memoryPages);
	freePages.size = 0;
	markOccupiedPages();
	//printMemoryPages();

}

void splitMemory(){
	void * memoryIndex = 0x000000;
	int i;
	for(i = 0; i < PAGEQUANTITY; i++){
		memoryPages[i].startingMemory = memoryIndex;
		memoryPages[i].occupied = 0;
		memoryIndex += 0x1000;
	}	
}

void markOccupiedPages(){
	memoryPages[0].occupied = 1;
	memoryPages[1].occupied = 1;
	memoryPages[2].occupied = 1;
	memoryPages[3].occupied = 1;
}

void printMemoryPages(){
	int i;
	for(i = 0; i < 35; i++){
		printHex((qword) memoryPages[i].startingMemory);
		nextLine();
	}	
}

void printFreePages(){
	int i = 0;
	print_string("Imprimiendo paginas libres: ");
	nextLine();
	while(i != freePages.size){
		print_string("Pagina libre: ");
		printHex(freePages.memoryFree[i]);
		nextLine();
		i++;
	}
}

void * allocPage(){
	void * page;
	if(freePages.size != 0){
		page = freePages.memoryFree[freePages.size - 1];
		freePages.size--;
	}else{
		page = searchForFreePage(memoryPages);
	}
	//if(page == NULL); //lanzaria una excepcion
	return page;
}

void * searchForFreePage(){
	int search = 1;
	int iteration = 0;
	void * page;
	while(search && iteration < PAGEQUANTITY){
		if(memoryPages[iteration].occupied == 0){
			search = 0;
			page = memoryPages[iteration].startingMemory;
			memoryPages[iteration].occupied = 1;
			//print_string("La pagina encontrada fue: ");
			//printHex(page);
			//print_string("La pagina encontrada fue: ");
			//nextLine();
		}
		iteration++;
	}
	return page;
}

void releasePage(Process process){
	recursiveRealeseHeap(process.heap);
	releaseStack(process.baseStack);
	//printFreePages();
}

void releaseStack(void * baseStack){
	freePages.memoryFree[freePages.size] = baseStack;
	freePages.size++;
}

void recursiveRealeseHeap(p_heapPage heap){
	if(heap == NULL)
		return;
	recursiveRealeseHeap(heap->nextHeapPage);
	freePages.memoryFree[freePages.size] = heap->currentPage;
	freePages.size++;
}
