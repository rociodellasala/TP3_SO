#ifndef MODULELOADER_H
#define MODULELOADER_H

#include "types.h"

/* */
void loadModules(void *, void **);

static void loadModule(byte **, void *);

static dword readUint32(byte **);

#endif
