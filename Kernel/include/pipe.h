#ifndef PIPE_H
#define PIPE_H

#include "structs.h"
#include "types.h"

#define READ_ACTION 0

/* */
p_pipe createPipe(int, int);

/* */
s_pipe createPipeStruct(int, int);

/* */
void printPipeInfo(p_pipe pipe);

/* */
int write(p_pipe pipe,char *, int, int);

/* */
int read(p_pipe pipe,char *, int, int);

/* */
void close(p_pipe pipe,int, int);

/* */
void open(p_pipe pipe, int, int);

#endif
