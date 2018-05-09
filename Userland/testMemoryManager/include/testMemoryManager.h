#ifndef TESTMEMORYMANAGER_H
#define TESTMEMORYMANAGER_H

void printStartTestMessage();

void printfFirstTestMessage();

void printfSecondTestMessage();

void printfThirdTestMessage(int, int);

void printfFourthTestMessage(int, int);

void * whenAskedForMemoryFirstPointer(int *);

void thenMemoryIsReserved(void *);

void * whenAskedForMemorySecondPointer(int *);

void thenBothPointersAreNotEqual(void *, void *);

void thenSecondPointerStartsWhereItShould(int, void *, void *);

void * whenAskedForMemoryThirdPointer(int *,int,int);

void thenAllPointersAreNotEqual(void *, void *, void *);

void thenThirdPointerStartsWhereItShould(void *);

void * whenAskedForMemoryFourthPointer(int *, int, int);

void thenAllTestPointersAreNotEqual(void *, void *, void *, void *);

void thenFourthPointerStartsWhereItShould(void *, int, int);

void exitTest();

void exitProgram();

#endif