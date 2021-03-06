#include "lib.h"
#include "moduleLoader.h"

void loadModules(void * payloadStart, void ** targetModuleAddress){
	int i;
	byte * currentModule = (byte *)payloadStart;
	dword moduleCount = readUint32(&currentModule);

	for (i = 0; i < moduleCount; i++)
		loadModule(&currentModule, targetModuleAddress[i]);
}

void loadModule(byte ** module, void * targetModuleAddress){
	dword moduleSize = readUint32(module);

	memcpy(targetModuleAddress, *module, moduleSize);
	*module += moduleSize;
}

dword readUint32(byte ** address){
	dword result = *(dword *)(*address);
	*address += sizeof(dword);
	return result;
}



