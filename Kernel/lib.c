#include <stdint.h>
#include <types.h>

void * memset(void * destination, dword c, qword length){
	byte chr = (byte)c;
	char * dst = (char *)destination;

	while(length--)
		dst[length] = chr;

	return destination;
}

void * memcpy(void * destination, const void * source, qword length){
	qword i;

	if ((qword)destination % sizeof(dword) == 0 
		&& (qword)source % sizeof(dword) == 0 && length % sizeof(dword) == 0){
		dword * d = (dword *) destination;
		const dword * s = (const dword *)source;

		for (i = 0; i < length / sizeof(dword); i++)
			d[i] = s[i];
	} else {
		byte * d = (byte *)destination;
		const byte * s = (const byte *)source;

		for (i = 0; i < length; i++)
			d[i] = s[i];
	}

	return destination;
}
