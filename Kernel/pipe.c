#include <pipe.h>
#include <scheduler.h>
#include <heap.h>
#include <lib.h>
#include <string.h>
#include <mutex.h>

p_pipe createPipe(int callingProcessPID, int connectingProcessPID){
		ProcessSlot * callingProcessSlot = getProcessFromPid(callingProcessPID);
		ProcessSlot * connectingProcessSlot = getProcessFromPid(connectingProcessPID);

		Process callingProcess = callingProcessSlot->process;
		Process connectingProcess = connectingProcessSlot->process;

		if(connectingProcess.pipe != NULL){
			return connectingProcess.pipe;
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

	pipeStruct.mutex = true;

	return pipeStruct;
}

void write(p_pipe pipe,char * messageSent,int msgLenght, int callingProcessPID){
	int messageSentLenght = strlen(messageSent);

	if(messageSentLenght > MAX_MESSAGE_LENGHT - pipe->messageIndex)
		return;

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
	
	return;
}

void read(p_pipe pipe,char * messageDestination,int charsToRead,int callingProcessPID){
	char * aux;

	if(charsToRead > MAX_MESSAGE_LENGHT)
		return;

	if(pipe->processOnePID == callingProcessPID && pipe->processOneRead == true){
		while(pipe->messageIndex == 0)
			blockProgram();
		pipe->mutex = wait(pipe->mutex);
		strncpy(messageDestination,pipe->message,charsToRead);
		aux = (pipe->message) + charsToRead;
		memset(pipe->message,0,MAX_MESSAGE_LENGHT);
		strcpy(pipe->message,aux);
		pipe->messageIndex = pipe->messageIndex - charsToRead + 1;
		pipe->mutex = signal();
	}else if(pipe->processTwoPID == callingProcessPID && pipe->processTwoWrite == true){
		while(pipe->messageIndex == 0)
			blockProgram();
		pipe->mutex = wait(pipe->mutex);
		strncpy(messageDestination,pipe->message,charsToRead);
		aux = (pipe->message) + charsToRead;
		memset(pipe->message,0,MAX_MESSAGE_LENGHT);
		strcpy(pipe->message,aux);
		pipe->messageIndex = pipe->messageIndex - charsToRead + 1;
		pipe->mutex = signal();
	}
	return;
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
