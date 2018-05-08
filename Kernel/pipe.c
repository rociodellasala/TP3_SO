#include "pipe.h"
#include "scheduler.h"
#include "heap.h"
#include "lib.h"
#include "string.h"
#include "mutex.h"
#include "converter.h"
#include "video_driver.h"

p_pipe createPipe(int callingProcessPID, int connectingProcessPID){
		ProcessSlot * callingProcessSlot = getProcessFromPid(callingProcessPID);
		ProcessSlot * connectingProcessSlot = getProcessFromPid(connectingProcessPID);


		Process callingProcess = callingProcessSlot->process;
		Process connectingProcess = connectingProcessSlot->process;

		if(connectingProcessSlot != NULL){
			if(connectingProcessSlot->process.pipe != NULL){
				connectingProcessSlot->process.pipe->processTwoPID = callingProcessPID;
				return connectingProcessSlot->process.pipe;
			}
		}

		s_pipe pipeStruct = createPipeStruct(callingProcessPID,connectingProcessPID);
		p_pipe pipePointer = &pipeStruct;
		int sizeOfPipe = sizeof(s_pipe);
		void * destination = findAvaiableHeapKernelPage(sizeOfPipe);
		pipePointer = memcpy(destination, pipePointer, sizeOfPipe);
		return pipePointer;
}

s_pipe createPipeStruct(int callingProcessPID, int connectingProcessPID){
	s_pipe pipeStruct;
	pipeStruct.processOnePID = callingProcessPID;
	pipeStruct.processTwoPID = connectingProcessPID;

	pipeStruct.processOneRead = true;
	pipeStruct.processOneWrite = true;
	pipeStruct.processTwoRead = true;
	pipeStruct.processTwoWrite = true;
	pipeStruct.messageIndex = 0;
	memset(pipeStruct.message,0,MAX_MESSAGE_LENGHT);

	pipeStruct.mutex = true;

	return pipeStruct;
}

/*
p_pipe searchPipe(int callingProcessPID, int connectingProcessPID){
	int i;
	for(i = 0; i < MAX_PIPES; i++){
		int processOnePID = pipes[i].processOnePID;
		int processTwoPID = pipes[i].processTwoPID;

		if( (processOnePID ==  callingProcessPID || processOnePID == connectingProcessPID) &&
			(processTwoPID ==  callingProcessPID || processTwoPID == connectingProcessPID)){
			return  pipes[i]
		}		
	}
	return NULL;
}
*/

void printPipeInfo(p_pipe pipe){
	nextLine();
	print_string("Pipe information:");
	nextLine();
	print_string("Pipe pointer: ");
	printHex(pipe);
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

int write(p_pipe pipe,char * messageSent,int msgLenght, int callingProcessPID){
	int messageSentLenght = strlen(messageSent);
	if(messageSentLenght > MAX_MESSAGE_LENGHT - pipe->messageIndex)
		return -1;

	if(pipe->processOnePID == callingProcessPID && pipe->processOneWrite == true){
		pipe->mutex = wait(pipe->mutex);
		strcpy((pipe->message) + pipe->messageIndex,messageSent);
		pipe->messageIndex += messageSentLenght;
		pipe->mutex = signal();
	}else if(pipe->processTwoPID == callingProcessPID && pipe->processTwoWrite == true){
		pipe->mutex = wait(pipe->mutex);
		strcpy((pipe->message) + pipe->messageIndex,messageSent);
		pipe->messageIndex += messageSentLenght;
		pipe->mutex = signal();
	}
	return msgLenght;
}

int read(p_pipe pipe,char * messageDestination,int charsToRead,int callingProcessPID){
	char aux[MAX_MESSAGE_LENGHT];
	if(charsToRead > MAX_MESSAGE_LENGHT)
		return -1;

	if(pipe->processOnePID == callingProcessPID && pipe->processOneRead == true){
		while(pipe->messageIndex == 0);
		pipe->mutex = wait(pipe->mutex);
		strncpy(messageDestination,pipe->message,charsToRead);
		strcpy(aux,pipe->message + charsToRead);
		memset(pipe->message,0,MAX_MESSAGE_LENGHT);
		strcpy(pipe->message,aux);
		pipe->messageIndex = pipe->messageIndex - charsToRead + 1;
		pipe->mutex = signal();
	}else if(pipe->processTwoPID == callingProcessPID && pipe->processTwoRead == true){
		while(pipe->messageIndex == 0);
		pipe->mutex = wait(pipe->mutex);
		strncpy(messageDestination,pipe->message,charsToRead);
		strcpy(aux,pipe->message + charsToRead);
		memset(pipe->message,0,MAX_MESSAGE_LENGHT);
		strcpy(pipe->message,aux);
		pipe->messageIndex = pipe->messageIndex - charsToRead;
		pipe->mutex = signal();
	}

	//printPipeInfo(pipe);
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
