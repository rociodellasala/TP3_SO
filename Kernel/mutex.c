#include "mutex.h"
#include "scheduler.h"

boolean wait(boolean mutex){
	if(mutex == false){
		unblockProcess(getCurrentPid());
	}
	return false;
}

boolean signal(){
	return true;
}