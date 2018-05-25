#ifndef MEMORYMANAGER_H
#define MEMORYMANAGER_H

#include "structs.h"
#include "types.h"

#define FREEPAGES 300
#define PAGEQUANTITY 262144 /* 1GB divided into 4KB */

#define PAGE_SIZE 4096
#define MAX_NODES 2049
#define MAX_FREE_NODES 300
#define INVALID_INDEX -1
#define EMPTY 0
#define PARTIALLY 1
#define FULL 2

typedef struct s_node * p_node;

typedef struct s_node{
	int size;
	int state;
	void * address;
	p_node left;
	p_node right;
}s_node;


typedef struct memoryManager
{
	int lastIndex;
	s_node nodes[MAX_NODES];
	int freeNodes[MAX_FREE_NODES];
}memoryManager;

/* Initialize memory manager by splitting the memory in pages of 4KB and initialize stack for released pages */ 
void initializeMemoryManager();

/*Creates the struct of a s_node*/
s_node createNode(void * address, int size);

/*Adds node to memory manager and returns it's pointer*/
p_node addNode(void * address, int size);

/*Moves all the array one position*/
void moveFreeArrayNodes(int * array);

/* Returns an unused partition */
void * allocPage(int sizeToAlloc);

/*Search for a free partition recursively*/
void * recursiveAlloc(int sizeToAlloc, p_node currentNode);

/*Return true if currentNode has sons, otherwise returns false*/
boolean hasSons(p_node currentNode);

/*Updates the node's state checking the states of the sons*/
void updateNodeState(p_node currentNode);

/*Splits memory block into 2 blocks*/
void splitBlock(p_node currentNode);

/*Transforms size into a multiple of 2*/
int transformSize(int size);

/*Release all pages reserved for a program's heap and stack*/
void releasePage(Process process);

/*Search for node location*/
void recursiveRelease(p_node currentNode,void * address, int size);

/*Search for all heap's of user's program*/
void recursiveSearchHeap(p_heapPage heap);

/*Add node Index to array of free nodes, to reuse it's structure*/
void addToFreeNodes(p_node currentNode);

/* Prints the actual buddy allocator tree information */
void printTree();

void recursivePrint(p_node currentNode, int lines);

char * getColorByState(p_node currentNode);

void printLines(int lines);

#endif
