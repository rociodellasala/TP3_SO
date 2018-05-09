#ifndef MUTEX_H
#define MUTEX_H

#include "types.h"

/*If mutex is not true, blocks the process, otherwise makes mutex flag to be false*/
boolean wait(boolean);

/*Makes mutex flag to be true*/
boolean signal();

#endif
