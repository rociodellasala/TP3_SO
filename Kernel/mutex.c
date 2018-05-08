#include <mutex.h>
#include <scheduler.h>

boolean wait(boolean mutex){
	while(mutex == false);
	return false;
}

boolean signal(){
	return true;
}