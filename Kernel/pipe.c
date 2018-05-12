#include "pipe.h"
#include "scheduler.h"
#include "heap.h"
#include "lib.h"
#include "string.h"
#include "mutex.h"
#include "converter.h"
#include "video_driver.h"
#include "process.h"

int pipePIDs = 0;

p_pipe createPipe(int callingProcessPID, int connectingProcessPID, char * connectingProcessName){
		ProcessSlot * connectingProcessSlot = getProcessFromPid(connectingProcessPID);
		ProcessSlot * callingProcessSlot = getProcessFromPid(callingProcessPID);
		int sizeOfPipe;	
		void * destination;
	
		p_pipe pipePointer = NULL;

		if(connectingProcessSlot != NULL){
			pipePointer = searchPipe(connectingProcessSlot,callingProcessSlot->process.processName,callingProcessPID);
		}
		if(pipePointer == NULL){
			s_pipe pipeStruct = createPipeStruct(callingProcessPID,-1, connectingProcessName);
			pipePointer = &pipeStruct;
			sizeOfPipe = sizeof(s_pipe);
			destination = findAvaiableHeapKernelPage(sizeOfPipe);
			pipePointer = memcpy(destination, pipePointer, sizeOfPipe);
		}
		return pipePointer;
}

s_pipe createPipeStruct(int callingProcessPID, int connectingProcessPID, char * connectingProcessName){
	s_pipe pipeStruct;

	pipeStruct.pipePID = pipePIDs++;

	pipeStruct.processOnePID = callingProcessPID;
	pipeStruct.processTwoPID = connectingProcessPID;
	strcpy(pipeStruct.processTwoName,connectingProcessName);

	pipeStruct.processOneRead = true;	
	pipeStruct.processOneWrite = true;
	pipeStruct.processTwoRead = true;
	pipeStruct.processTwoWrite = true;
	pipeStruct.messageIndex = 0;
	memset(pipeStruct.message,0,MAX_MESSAGE_LENGHT);

	pipeStruct.mutex = getFreeMutex(connectingProcessName);

	return pipeStruct;
}


p_pipe searchPipe(ProcessSlot * connectingProcessSlot,char * callingProcessName, int callingProcessPID){
	int i;
	for(i = 0; i < connectingProcessSlot->process.pipeIndex; i++){
		if(connectingProcessSlot->process.pipes[i]->processTwoPID == INVALID_PID && 
			strcmp(connectingProcessSlot->process.pipes[i]->processTwoName,callingProcessName)){
			connectingProcessSlot->process.pipes[i]->processTwoPID = callingProcessPID;
			connectingProcessSlot->process.pipeIndex++;
			return connectingProcessSlot->process.pipes[i];
		}	
	}
	return NULL;
}

p_pipe searchPipeByPID(ProcessSlot * callingProcessSlot, int pipePID){
	int pipeIndex = callingProcessSlot->process.pipeIndex;
	int i;

	for(i = 0; i < pipeIndex; i++){
		if(callingProcessSlot->process.pipes[i]->pipePID == pipePID)
			return callingProcessSlot->process.pipes[i];
	}
	return NULL;
}

/*
void printPipeInfo(p_pipe pipe){
	nextLine();
	print_string("Pipe information:");
	nextLine();
	print_string("Pipe pointer: ");
	printHex((qword)pipe);
	nextLine();
	print_string("PID 1: ");
	print_int(pipe->processOnePID);
	nextLine();
	int pid2 = pipe->processTwoPID;
	print_string("PID 2: ");
	if(pid2 < 0){
		print_string("-");
		print_int(pid2 * -1);
		nextLine();
	}else{
		print_int(pid2);
		nextLine();
	}
	print_string("Process 1 permission to read: ");
	print_int(pipe->processOneRead);
	nextLine();
	print_string("Process 2 permission to read: ");
	print_int(pipe->processTwoRead);
	nextLine();
	print_string("Process 1 permission to write: ");
	print_int(pipe->processOneWrite);
	nextLine();
	print_string("Process 2 permission to write: ");
	print_int(pipe->processTwoWrite);
	nextLine();
	print_string("Actual message:");
	print_string(pipe->message);
	nextLine();
	print_string("Actual message index:");
	print_int(pipe->messageIndex);
	nextLine();
	print_string("MUTEX: ");
	print_int(pipe->mutex);
	nextLine();
	nextLine();
	nextLine();
}
*/
int write(p_pipe pipe,char * messageSent,int msgLenght, int callingProcessPID){
	int messageSentLenght = strlen(messageSent);
	if(messageSentLenght > MAX_MESSAGE_LENGHT - pipe->messageIndex)
		return -1;

	if(pipe->processOnePID == callingProcessPID && pipe->processOneWrite == true){
		wait(pipe->mutex);
		strcpy((pipe->message) + pipe->messageIndex,messageSent);
		pipe->messageIndex += messageSentLenght;
		signal(pipe->mutex);
	} else if(pipe->processTwoPID == callingProcessPID && pipe->processTwoWrite == true){
		wait(pipe->mutex);
		strcpy((pipe->message) + pipe->messageIndex,messageSent);
		pipe->messageIndex += messageSentLenght;
		signal(pipe->mutex);
	} 

	return msgLenght;
}

int read(p_pipe pipe,char * messageDestination,int charsToRead,int callingProcessPID){
	char aux[MAX_MESSAGE_LENGHT];
	if(charsToRead > MAX_MESSAGE_LENGHT)
		return 0;
	if(pipe->processOnePID == callingProcessPID && pipe->processOneRead == true){
		if(pipe->messageIndex == 0){
			blockProcess(callingProcessPID);
			return -1;
		}
		wait(pipe->mutex);
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
		wait(pipe->mutex);
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
