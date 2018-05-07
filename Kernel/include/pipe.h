#ifndef PIPE_H
#define PIPE_H

#include "structs.h"

#define READ_ACTION 0

p_pipe createPipe(int callingProcessPID, int connectingProcessPID);

s_pipe createPipeStruct(int callingProcessPID, int connectingProcessPID);

void write(p_pipe pipe,char * messageSent,int msgLenght, int callingProcessPID);

void read(p_pipe pipe,char * messageDestination,int charsToRead,int callingProcessPID);

void close(p_pipe pipe,int action,int callingProcessPID);

void open(p_pipe pipe,int action,int callingProcessPID);




#endif