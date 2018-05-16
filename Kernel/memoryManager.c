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
	newNode.avaiable = true;
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
	if(currentNode->avaiable == false)
		return NULL;

	if(hasSons(currentNode)){
		addressToReturn = recursiveAlloc(sizeToAlloc,currentNode->left);
		if(addressToReturn == NULL)
			addressToReturn = recursiveAlloc(sizeToAlloc,currentNode->right);
		if(currentNode->left->avaiable == false && currentNode->right->avaiable == false)
			currentNode->avaiable = false;
		return addressToReturn;
	}else{
		if(currentNode->size < sizeToAlloc)
			return NULL;
		else if(currentNode->size / 2 >= sizeToAlloc){
			currentNode->left = addNode(currentNode->address,currentNode->size / 2);
			currentNode->right = addNode(currentNode->address + currentNode->size / 2,currentNode->size / 2);
			return recursiveAlloc(sizeToAlloc,currentNode->left);
		}else{
			currentNode->avaiable = false;
			return currentNode->address;
		}
	}
}

boolean hasSons(p_node currentNode){
	if(currentNode->left != NULL || currentNode->right != NULL)
		return true;
	else
		return false;
}

int transformSize(int size){
	int module[22] = {1,2,4,8,16,32,64,128,256,512,1024,2048,4096,8192,16384,32768,65536,131072,262144,524288,1048576,2097152};
	int i;

	for(i = 0; i < 21; i++){
		if(module[i] == size)
			return size;
		else if(module[i] > size)
			return module[i];
	}

	return size;
}

void releasePage(Process process){
	recursiveRelease(&memoryManagerPointer->nodes[0],process.baseStack,PAGE_SIZE);
	recursiveSearchHeap(process.heap);
}

boolean recursiveRelease(p_node currentNode,void * address, int size){
	boolean join = true;
	if(currentNode == NULL)
		return true;

	if(! hasSons(currentNode) && (address != currentNode->address || size != currentNode->size))
		return false;

	if(! hasSons(currentNode) && address == currentNode->address && size == currentNode->size){
		currentNode->avaiable = true;
		return true;
	}

	if(address != currentNode->address || size != currentNode->size){
		join = recursiveRelease(currentNode->left,address,size) & recursiveRelease(currentNode->right,address,size);
		if(currentNode->left->avaiable == true || currentNode->right->avaiable == true)
			currentNode->avaiable = true;
		if(join == true){
			addToFreeNodes(currentNode->left);
			addToFreeNodes(currentNode->right);
			currentNode->left = NULL;
			currentNode->right = NULL;
			currentNode->avaiable = true;
		}
		return join;
	}
	return false;
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
