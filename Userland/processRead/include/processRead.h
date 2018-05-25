#ifndef PROCESSREAD_H
#define PROCESSREAD_H

/*Prints starting message of test */
void printStaringMessageTest();

/*Reserves memory for string */
char * givenStringToStore(int);

/*Use read function to read from a pipe */
void whenStringIsReceived(char *, int, int);

/*Checks if first test is succesful */
void thenFirstStringIsReceived(char *);

/*Checks if second test is succesful */
void thenSecondStringIsReceived(char *);

#endif
