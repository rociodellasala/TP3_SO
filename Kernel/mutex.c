#include <mutex.h>
#include <scheduler.h>

boolean wait(boolean mutex){
	while(mutex == false){
		blockProgram();
	}
	return false;
}

boolean signal(){
	return true;
}