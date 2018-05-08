#ifndef EXCEPTION_H
#define EXCEPTION_H

#include "types.h"

/* Dispatches the exception to the corresponding driver */
void exceptionDispatcher(int , qword *);

/* Displays the values ​​of the registers at the time the exception occurred */
void zero_divisionHandler(qword *);
void invalid_opcodeHandler(qword *);

void showRegistersValues(qword *);

#endif
