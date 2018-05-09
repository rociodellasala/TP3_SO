#ifndef PIPE_H
#define PIPE_H

#include "structs.h"
#include "types.h"

#define READ_ACTION 0

/*Creates a IPC structure pointer for 2 programs*/
p_pipe createPipe(int callingProcessPID, int connectingProcessPID, char * connectingProcessName);

/*Creates a IPC structure for 2 programs*/
s_pipe createPipeStruct(int callingProcessPID, int connectingProcessPID, char * connectingProcessName);

/*Search for a pipe that is waiting for a program to start communication*/
p_pipe searchPipe(ProcessSlot * connectingProcessSlot,char * callingProcessName, int callingProcessPID);

/*Search a pipe by PID in a process structure*/
p_pipe searchPipeByPID(ProcessSlot * callingProcessSlot, int pipePID);

/*Just prints all the information of the pipe for debugging*/
void printPipeInfo(p_pipe pipe);

/*Writes through the IPC structure*/
int write(p_pipe pipe,char *, int, int);

/*Reads through the IPC structure*/
int read(p_pipe pipe,char *, int, int);

/*makes a process unable to write or read*/
void close(p_pipe pipe,int, int);

/*makes a process able to write or read*/
void open(p_pipe pipe, int, int);

#endif
