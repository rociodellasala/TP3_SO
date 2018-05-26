#include "converter.h"
#include "memoryManager.h"
#include "structs.h"
#include "types.h"
#include "video_driver.h"
#include "lib.h"

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

void * allocPage(int sizeToAlloc){
	void * addressToReturn = NULL;
	sizeToAlloc = transformSize(sizeToAlloc);

	addressToReturn = recursiveAlloc(sizeToAlloc, &memoryManagerPointer->nodes[0]);

	return addressToReturn;
}

void * recursiveAlloc(int sizeToAlloc, p_node currentNode){
	void * addressToReturn = NULL;
	if(currentNode->state == FULL)
		return NULL;

	if(hasSons(currentNode)){
		addressToReturn = recursiveAlloc(sizeToAlloc,currentNode->left);
		if(addressToReturn == NULL)
			addressToReturn = recursiveAlloc(sizeToAlloc,currentNode->right);
		updateNodeState(currentNode);
		return addressToReturn;
	}else{
		if(currentNode->size < sizeToAlloc)
			return NULL;
		else if(currentNode->size / 2 >= sizeToAlloc){
			splitBlock(currentNode);
			return recursiveAlloc(sizeToAlloc,currentNode->left);
		}else{
			currentNode->state = FULL;
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
	currentNode->right = addNode(currentNode->address + currentNode->size / 2,currentNode->size / 2);
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
	recursiveRelease(&memoryManagerPointer->nodes[0],process.baseStack,PAGE_SIZE);
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

	for(i = 0; i < MAX_NODES; i++){
		if(&memoryManagerPointer->nodes[i] == currentNode)
			break;
	}

	for(i = 0; i < MAX_FREE_NODES; i++){
		if(memoryManagerPointer->freeNodes[i] == INVALID_INDEX)
			memoryManagerPointer->freeNodes[i] = i;
	}

	return;
}


void printTree(){
	nextLine();
	print_stringColor("                           ------------MEMORY INFORMATION STATE------------", "blue");
	nextLine();
	recursivePrint(&memoryManagerPointer->nodes[0],0,0);
}

void recursivePrint(p_node currentNode, int lines, int level){
	char * color;
	if(currentNode == NULL)
		return;
	color = getColorByState(currentNode);
	printLines(lines,level);
	print_stringColor("STATE  ", color);
	print_string(" 0x");
	printHex(currentNode->address);
	nextLine();
	recursivePrint(currentNode->left, lines + 2,level + 1);
	recursivePrint(currentNode->right, lines + 2,level + 1);
}

char * getColorByState(p_node currentNode){
	if(currentNode->state == EMPTY)
		return "green";
	else if(currentNode->state == PARTIALLY)
		return "yellow";
	else
		return "red";
}

void printLines(int lines, int level){
	int i;

	if(lines == 0){
		print_int(level);
		print_string(")");
	}

	for(i = 0; i < lines; i++){
		print_string("  ");
		if(i == lines - 1){
			print_int(level);
			print_string(")");
		}
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

	if(! hasSons(currentNode)){
		print_stringColor("$$$$$$$  ",getColorByState(currentNode));
		print_string("0x");
		printHex(currentNode->address);
		print_string(" Process:");
		nextLine();
	}

	verticalRecursivePrint(currentNode->left);
	verticalRecursivePrint(currentNode->right);
}

