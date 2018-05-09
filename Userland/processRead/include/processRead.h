#ifndef PROCESSREAD_H
#define PROCESSREAD_H

void printStaringMessageTest();

char * givenStringToStore(int);

void whenStringIsReceived(char *, int, int);

void thenFirstStringIsReceived(char const *);

void thenSecondStringIsReceived(char const *);

#endif
