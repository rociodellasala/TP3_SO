#ifndef PROCESSREAD_H
#define PROCESSREAD_H

void printStaringMessageTest();

char * givenStringToStore(int size);

void whenStringIsReceived(char * firstString, int charsToRead, int pid);

void thenFirstStringIsReceived(char const * firstString);

void thenSecondStringIsReceived(char const * secondString);


#endif