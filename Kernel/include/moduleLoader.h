#ifndef MODULELOADER_H
#define MODULELOADER_H

#include "types.h"

void loadModules(void *, void **);

void loadModule(byte **, void *);

dword readUint32(byte **);

#endif
