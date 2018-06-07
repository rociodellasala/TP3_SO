#include "pipe.h"
#include "scheduler.h"
#include "heap.h"
#include "lib.h"
#include "string.h"
#include "mutex.h"
#include "converter.h"
#include "video_driver.h"
#include "process.h"

extern kernelHeapHeader * kernelHeader;

int pipePIDs = 0;

p_pipe createPipe(int callingProcessPID, int connectingProcessPID){
		ProcessSlot * connectingProcessSlot = getProcessFromPid(connectingProcessPID);
		ProcessSlot * callingProcessSlot = getProcessFromPid(callingProcessPID);
		int sizeOfPipe;	
		void * destination;
	
		p_pipe pipePointer = NULL;

		if(connectingProcessSlot != NULL){
			pipePointer = searchPipe(connectingProcessSlot,callingProcessSlot->process.processName,callingProcessPID);
		}
		if(pipePointer == NULL){
			s_pipe pipeStruct = createPipeStruct(callingProcessPID,connectingProcessPID);
			pipePointer = &pipeStruct;
			sizeOfPipe = sizeof(s_pipe);
			destination = findAvaiableHeapKernelPage(sizeOfPipe);
			pipePointer = memcpy(destination, pipePointer, sizeOfPipe);
		}
		printPipeInfo(pipePointer);
		return pipePointer;
}

s_pipe createPipeStruct(int callingProcessPID, int connectingProcessPID){
	s_pipe pipeStruct;

	pipeStruct.pipePID = pipePIDs++;

	pipeStruct.processOnePID = callingProcessPID;
	pipeStruct.processTwoPID = connectingProcessPID;

	pipeStruct.full = false;

	pipeStruct.processOneRead = true;	
	pipeStruct.processOneWrite = true;
	pipeStruct.processTwoRead = true;
	pipeStruct.processTwoWrite = true;
	pipeStruct.messageIndex = 0;
	memset(pipeStruct.message,0,MAX_MESSAGE_LENGHT);

	pipeStruct.mutex = getFreeMutex(getProcessFromPid(connectingProcessPID)->process.processName);
	return pipeStruct;
}


p_pipe searchPipe(ProcessSlot * connectingProcessSlot,char * callingProcessName, int callingProcessPID){
	int i;
	for(i = 0; i < connectingProcessSlot->process.pipeIndex; i++){
		if(connectingProcessSlot->process.pipes[i]->processTwoPID == callingProcessPID && connectingProcessSlot->process.pipes[i]->full == false){
			connectingProcessSlot->process.pipes[i]->full = true;
			return connectingProcessSlot->process.pipes[i];
		}	
	}
	return NULL;
}

p_pipe searchPipeByPID(ProcessSlot * callingProcessSlot, int pipePID){
	int pipeIndex = callingProcessSlot->process.pipeIndex;
	int i;

	for(i = 0; i < pipeIndex; i++){
		if(callingProcessSlot->process.pipes[i]->pipePID == pipePID){
			return callingProcessSlot->process.pipes[i];
		}
	}
	return NULL;
}


void printPipeInfo(p_pipe pipe){
	int pid2 = pipe->processTwoPID;
	nextLineAnyway();
	print_stringColor("*******************Kernel message*******************","yellow");
	nextLineAnyway();
	nextLineAnyway();
	print_stringColor("Pipe PID: ","white");
	print_intColor(pipe->pipePID,"white");
	nextLineAnyway();
	print_stringColor("Process connected:     ","white");
	print_stringColor("PID 1: ","white");
	print_intColor(pipe->processOnePID,"white");
	print_stringColor("     ","white");
	print_stringColor("PID 2: ","white");
	if(pid2 < 0){
		print_stringColor("-","white");
		print_intColor(pid2 * -1,"white");
		nextLineAnyway();
	}else{
		print_intColor(pid2,"white");
		nextLineAnyway();
	}
	if(pipe->full == false)
		print_stringColor("STATUS: FREE","green");
	else
		print_stringColor("STATUS: FULL","red");
	nextLineAnyway();
	nextLineAnyway();
	print_stringColor("*****************End kernel message*****************","yellow");
	nextLineAnyway();
	nextLineAnyway();
}

int write(p_pipe pipe,char * messageSent,int msgLenght, int callingProcessPID){
	int mutexLock;
	if(msgLenght > MAX_MESSAGE_LENGHT - pipe->messageIndex)
		return LOCK;
	if(pipe->processOnePID == callingProcessPID && pipe->processOneWrite == true){
		mutexLock = wait(pipe->mutex);
		if(mutexLock == LOCK)
			return LOCK;
		strcpy((pipe->message) + pipe->messageIndex,messageSent);
		pipe->messageIndex += msgLenght;
		signal(pipe->mutex);
		unblockProcess(pipe->processTwoPID);
	} else if(pipe->processTwoPID == callingProcessPID && pipe->processTwoWrite == true){
		mutexLock = wait(pipe->mutex);
		if(mutexLock == LOCK)
			return LOCK;
		strcpy((pipe->message) + pipe->messageIndex,messageSent);
		pipe->messageIndex += msgLenght;
		signal(pipe->mutex);
		unblockProcess(pipe->processOnePID);
	} 
	return msgLenght;
}

int read(p_pipe pipe,char * messageDestination,int charsToRead,int callingProcessPID){
	char aux[MAX_MESSAGE_LENGHT];
	int mutexLock;
	if(charsToRead > MAX_MESSAGE_LENGHT)
		return 0;
	if(pipe->processOnePID == callingProcessPID && pipe->processOneRead == true){
		if(pipe->messageIndex == 0){
			blockProcess(callingProcessPID);
			return LOCK;
		}
		mutexLock = wait(pipe->mutex);
		if(mutexLock == LOCK)
			return LOCK;
		strncpy(messageDestination,pipe->message,charsToRead);
		strcpy(aux,pipe->message + charsToRead);
		memset(pipe->message,0,MAX_MESSAGE_LENGHT);
		strcpy(pipe->message,aux);
		pipe->messageIndex = pipe->messageIndex - charsToRead + 1;
		signal(pipe->mutex);
	} else if(pipe->processTwoPID == callingProcessPID && pipe->processTwoRead == true){
		if(pipe->messageIndex == 0){
			blockProcess(callingProcessPID);
			return -1;
		}
		mutexLock = wait(pipe->mutex);
		if(mutexLock == LOCK)
			return LOCK;
		strncpy(messageDestination,pipe->message,charsToRead);
		strcpy(aux,pipe->message + charsToRead);
		memset(pipe->message,0,MAX_MESSAGE_LENGHT);
		strcpy(pipe->message,aux);
		pipe->messageIndex = pipe->messageIndex - charsToRead;
		signal(pipe->mutex);
	}
	return charsToRead;

}

void close(p_pipe pipe,int action,int callingProcessPID){
	if(pipe->processOnePID == callingProcessPID){
		if(action == READ_ACTION)
			pipe->processOneRead = 0;
		else
			pipe->processOneWrite = 0;
	}else{
		if(action == READ_ACTION)
			pipe->processTwoRead = 0;
		else
			pipe->processTwoWrite = 0;
	}
	return;
}

void open(p_pipe pipe,int action,int callingProcessPID){
	if(pipe->processOnePID == callingProcessPID){
		if(action == READ_ACTION)
			pipe->processOneRead = 1;
		else
			pipe->processOneWrite = 1;
	}else{
		if(action == READ_ACTION)
			pipe->processTwoRead = 1;
		else
			pipe->processTwoWrite = 1;
	}
	return;
}
