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
	/*
	* memcpy does not support overlapping buffers, so always do it
	* forwards. (Don't change this without adjusting memmove.)
	*
	* For speedy copying, optimize the common case where both pointers
	* and the length are word-aligned, and copy word-at-a-time instead
	* of byte-at-a-time. Otherwise, copy by bytes.
	*
	* The alignment logic below should be portable. We rely on
	* the compiler to be reasonably intelligent about optimizing
	* the divides and modulos out. Fortunately, it is.
	*/
	qword i;

	if ((qword)destination % sizeof(dword) == 0 &&
		(qword)source % sizeof(dword) == 0 &&
		length % sizeof(dword) == 0)
	{
		dword * d = (dword *) destination;
		const dword * s = (const dword *)source;

		for (i = 0; i < length / sizeof(dword); i++)
			d[i] = s[i];
	}
	else
	{
		byte * d = (byte *)destination;
		const byte * s = (const byte *)source;

		for (i = 0; i < length; i++)
			d[i] = s[i];
	}

	return destination;
}
