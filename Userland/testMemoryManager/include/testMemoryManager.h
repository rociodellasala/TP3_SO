#ifndef TESTMEMORYMANAGER_H
#define TESTMEMORYMANAGER_H

void printStartTestMessage();

void printfFirstTestMessage();

void printfSecondTestMessage();

void printfThirdTestMessage(int firstAmount, int secondAmount);

void printfFourthTestMessage(int firstAmount, int secondAmount);

void * whenAskedForMemoryFirstPointer(int * firstAmount);

void thenMemoryIsReserved(void * firstPointer);

void * whenAskedForMemorySecondPointer(int * secondAmount);

void thenBothPointersAreNotEqual(void * firstPointer, void * secondPointer);

void thenSecondPointerStartsWhereItShould(int firstAmount, void * firstPointer, void * secondPointer);

void * whenAskedForMemoryThirdPointer(int * thirdAmount,int firstAmount,int secondAmount);

void thenAllPointersAreNotEqual(void * firstStringPointer, void * secondStringPointer, void * thirdStringPointer);

void thenThirdPointerStartsWhereItShould(void * thirdStringPointer);

void * whenAskedForMemoryFourthPointer(int * fourthAmount, int firstAmount, int secondAmount);

void thenAllTestPointersAreNotEqual(void * firstStringPointer, void * secondStringPointer, void * thirdStringPointer, void * fourthStringPointer);

void thenFourthPointerStartsWhereItShould(void * fourthStringPointer, int firstAmount, int secondAmount);

void exitTest();

void exitProgram();

#endif