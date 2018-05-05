#include <assert.h>

boolean assertEqualPointer(void * first, void * second){
	if(first == second)
		return true;
	else
		return false;
}