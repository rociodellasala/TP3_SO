#include "converter.h"
#include "memoryManager.h"
#include "structs.h"
#include "types.h"
#include "video_driver.h"
#include "lib.h"
#include "string.h"

/*Address to storage memoryManagerStruct*/
static void * memoryManagerAddress = (void *) 0x40000;

/*Bytes in 1 GB*/
static const long allMemoryBytes = 1073741824;

memoryManager * memoryManagerPointer;


void initializeMemoryManager(){
	int memoryManagerSize = sizeof(memoryManager);
	int i;

	memoryManagerPointer = memcpy(memoryManagerAddress,memoryManagerPointer,memoryManagerSize);

	memoryManagerPointer->lastIndex = 0;
	for(i = 0; i < MAX_FREE_NODES; i++)
		memoryManagerPointer->freeNodes[i] = INVALID_INDEX;	

	addNode(NULL,allMemoryBytes);
	return;
}

s_node createNode(void * address, int size){
	s_node newNode;

	newNode.size = size;
	newNode.state = EMPTY;
	newNode.address = address;
	newNode.left = NULL;
	newNode.right = NULL;

	return newNode;
}

p_node addNode(void * address, int size){
	s_node newNode = createNode(address,size);
	p_node returnNodePointer;

	if(memoryManagerPointer->freeNodes[0] == INVALID_INDEX){
		memoryManagerPointer->nodes[memoryManagerPointer->lastIndex] = newNode;
		memoryManagerPointer->lastIndex++;
		returnNodePointer = &memoryManagerPointer->nodes[memoryManagerPointer->lastIndex - 1];
	}else{
		memoryManagerPointer->nodes[memoryManagerPointer->freeNodes[0]] = newNode;
		returnNodePointer = &memoryManagerPointer->nodes[memoryManagerPointer->freeNodes[0]];
		moveFreeArrayNodes(memoryManagerPointer->freeNodes);
	}

	return returnNodePointer;
}

void moveFreeArrayNodes(int * array){
	int i;

	for(i = 0; i < MAX_FREE_NODES - 1; i++)
		array[i] = array[i + 1];

	array[i] = INVALID_INDEX;
	return;
}

void * allocPage(int sizeToAlloc,char * processName){
	void * addressToReturn;
	sizeToAlloc = transformSize(sizeToAlloc);

	addressToReturn = recursiveAlloc(sizeToAlloc, &memoryManagerPointer->nodes[0], processName);

	return addressToReturn;
}

void * recursiveAlloc(int sizeToAlloc, p_node currentNode, char * processName){
	void * addressToReturn = NULL;
	if(currentNode->state == FULL)
		return NULL;

	if(hasSons(currentNode)){
		addressToReturn = recursiveAlloc(sizeToAlloc,currentNode->left,processName);
		if(addressToReturn == NULL)
			addressToReturn = recursiveAlloc(sizeToAlloc,currentNode->right,processName);
		updateNodeState(currentNode);
		return addressToReturn;
	}else{
		if(currentNode->size < sizeToAlloc)
			return NULL;
		else if(currentNode->size / 2 >= sizeToAlloc){
			splitBlock(currentNode);
			return recursiveAlloc(sizeToAlloc,currentNode->left,processName);
		}else{
			currentNode->state = FULL;
			strcpy(currentNode->process,processName);
			return currentNode->address;
		}
	}
}

void updateNodeState(p_node currentNode){
	if(currentNode->left->state == FULL && currentNode->right->state == FULL)
		currentNode->state = FULL;
	else if(currentNode->left->state == PARTIALLY || currentNode->right->state == PARTIALLY)
		currentNode->state = PARTIALLY;
	else if(currentNode->left->state == FULL || currentNode->right->state == FULL)
		currentNode->state = PARTIALLY;
	else
		currentNode->state = EMPTY;
}

void splitBlock(p_node currentNode){
	currentNode->left = addNode(currentNode->address,currentNode->size / 2);
	currentNode->right = addNode((char *) currentNode->address + currentNode->size / 2,currentNode->size / 2);
	currentNode->state = PARTIALLY;
}

boolean hasSons(p_node currentNode){
	if(currentNode->left != NULL || currentNode->right != NULL)
		return true;
	else
		return false;
}

int transformSize(int size){
	int returnSize = 1;

	while(returnSize < size)
		returnSize *= 2;
	return returnSize;
}

void releasePage(Process process){
	recursiveRelease(&memoryManagerPointer->nodes[0],process.currentThread->thread.baseStack,PAGE_SIZE);
	recursiveSearchHeap(process.heap);
}


void recursiveRelease(p_node currentNode,void * address, int size){

	if(hasSons(currentNode)){
		if(address < currentNode->right->address)
			recursiveRelease(currentNode->left,address,size);
		else
			recursiveRelease(currentNode->right,address,size);
		updateNodeState(currentNode);
		if(currentNode->state == EMPTY)
			releaseSons(currentNode);
	}else
		currentNode->state = EMPTY;
	return;
}

void releaseSons(p_node currentNode){
	addToFreeNodes(currentNode->left);
	addToFreeNodes(currentNode->right);
	currentNode->left = NULL;
	currentNode->right = NULL;
}

void recursiveSearchHeap(p_heapPage heap){
	if(heap == NULL)
		return;
	else	
		recursiveSearchHeap(heap->nextHeapPage);

	recursiveRelease(&memoryManagerPointer->nodes[0],heap->currentPage,PAGE_SIZE);


}

void addToFreeNodes(p_node currentNode){
	int i;
	int indexFree;

	for(i = 0; i < MAX_NODES; i++){
		if(&memoryManagerPointer->nodes[i] == currentNode){
			indexFree = i;
			break;
		}
	}

	for(i = 0; i < MAX_FREE_NODES; i++){
		if(memoryManagerPointer->freeNodes[i] == INVALID_INDEX){
			memoryManagerPointer->freeNodes[i] = indexFree;
			break;
		}
	}

	return;
}


void printTree(){
	boolean doLines[18] = {0};
	nextLine();
	print_stringColor("                           ------------MEMORY INFORMATION STATE------------", "blue");
	nextLine();
	recursivePrint(&memoryManagerPointer->nodes[0],0,doLines,false);
}

void recursivePrint(p_node currentNode,int level,boolean * doLines,boolean isLeft){
	char * color;
	if(currentNode == NULL)
		return;

	if(isLeft){
		doLines[level - 1] = true;
	}else{
		doLines[level - 1] = false;
	}
	color = getColorByState(currentNode);
	printLines(level,doLines,isLeft);
	print_stringColor("STATE ", color);
	print_string(" 0x");
	printHex((qword) currentNode->address);
	nextLine();
	recursivePrint(currentNode->left,level + 1,doLines,true);
	recursivePrint(currentNode->right,level + 1,doLines,false);
}

char * getColorByState(p_node currentNode){
	if(currentNode->state == EMPTY)
		return "green";
	else if(currentNode->state == PARTIALLY)
		return "yellow";
	else
		return "red";
}

void printLines(int level,boolean * doLines, boolean isLeft){
    int i;
    int doLinesIndex = 0;
    for(i = 1; i < level * 4 + 1; i++){
        if(i == level * 4 && ! isLeft){
               print_char('└');
               print_char('─');
        }
        else if(i == level * 4 && isLeft){
               print_char('├');
               print_char('─');	
        }
        else if(i % 4 == 0 && doLines[doLinesIndex] == true){
            print_char('│');
            doLinesIndex++;
        }
        else if(i % 4 == 0 && doLines[doLinesIndex] == false){
            print_string(" ");
            doLinesIndex++;
        }else
        	print_string(" ");
    }
}

void printVerticalMemory(){
	nextLine();
	print_stringColor("                           ------------MEMORY INFORMATION STATE------------", "green");
	nextLine();
	verticalRecursivePrint(&memoryManagerPointer->nodes[0]);
}

void verticalRecursivePrint(p_node currentNode){
	if(currentNode == NULL)
		return;

	if(! hasSons(currentNode))
		printMemory(getColorByState(currentNode),currentNode);
	
	verticalRecursivePrint(currentNode->left);
	verticalRecursivePrint(currentNode->right);
}


void printMemory(char * color,p_node node){
	printBlocks(color);
	print_string("0x");
	printHex((qword) node->address);
	nextLine();
	if(strcmp(color,"red")){
		printBlocks(color);
		print_string("Process: ");
		print_string(node->process);
		nextLine();
		printBlocks(color);
		print_string("0x");
		printHex((qword) node->address + node->size - 1);
		nextLine();
	}


}

void printBlocks(char * color){
	int i;
	int hexColor = getColorHex(color);
	for(i = 0; i < 11; i++){
		print_charColor('█',hexColor);
	}

	print_string("  ");
}



