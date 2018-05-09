#ifndef TESTMEMORYMANAGER_H
#define TESTMEMORYMANAGER_H

/*Prints starting test message*/
void printStartTestMessage();

/*Prints first test message*/
void printfFirstTestMessage();

/*Prints second test message*/
void printfSecondTestMessage();

/*Prints third test message*/
void printfThirdTestMessage(int, int);

/*Prints fourth test message*/
void printfFourthTestMessage(int, int);

/*Returns a void * after executing malloc*/
void * whenAskedForMemoryFirstPointer(int *);

/*Checks if first test is succesful*/
void thenMemoryIsReserved(void *);

/*Returns a void * after executing malloc*/
void * whenAskedForMemorySecondPointer(int *);

/*Checks if both pointers are equal or not*/
void thenBothPointersAreNotEqual(void *, void *);

/*Checks if second test is succesful*/
void thenSecondPointerStartsWhereItShould(int, void *, void *);

/*Returns a void * after executing malloc*/
void * whenAskedForMemoryThirdPointer(int *, int, int);

/*Checks that all pointers are different*/
void thenAllPointersAreNotEqual(void *, void *, void *);

/*Checks if third test is succesful*/
void thenThirdPointerStartsWhereItShould(void *);

/*Returns a void * after executing malloc*/
void * whenAskedForMemoryFourthPointer(int *, int, int);

/*Checks that all pointers are different*/
void thenAllTestPointersAreNotEqual(void *, void *, void *, void *);

/*Checks if fourth test is succesful*/
void thenFourthPointerStartsWhereItShould(void *, int, int);

void exitTest();

void exitProgram();

#endif