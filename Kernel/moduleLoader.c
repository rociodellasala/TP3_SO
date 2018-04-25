#include <stdint.h>
#include <lib.h>
#include <moduleLoader.h>
#include <types.h>


static void loadModule(byte ** module, void * targetModuleAddress);
static dword readUint32(byte ** address);

void loadModules(void * payloadStart, void ** targetModuleAddress){
	int i;
	byte * currentModule = (byte *)payloadStart;
	dword moduleCount = readUint32(&currentModule);

	for (i = 0; i < moduleCount; i++)
		loadModule(&currentModule, targetModuleAddress[i]);
}

static void loadModule(byte ** module, void * targetModuleAddress){
	dword moduleSize = readUint32(module);

	memcpy(targetModuleAddress, *module, moduleSize);
	*module += moduleSize;

}

static dword readUint32(byte ** address){
	dword result = *(dword *)(*address);
	*address += sizeof(dword);
	return result;
}



