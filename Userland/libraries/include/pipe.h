#ifndef PIPE_H
#define PIPE_H

#define BLOCKPROCESS -1

/* Call system call to create a pipe*/
int pipe(char *);

/* Call system call to write through a pipe*/
int write(int, char *, int);

/* Call system call to read through a pipe*/
int read(int, char *, int);

/* Call system call to make a process unable to write or read*/
void close(int, int);

/* Call system call to make a process able to write or read*/
void open(int, int);

#endif
