include ../Makefile.inc

MODULE=consumer.bin
ASMSOURCES= $(wildcard ../libraries/asm/*.asm)
SOURCES=$(wildcard [^_]*.c)
LIBRARYSOURCES=$(wildcard ../libraries/[^_]*.c)
LIBRARYOBJECTS=$(LIBRARYSOURCES:.c=.o)
ASMOBJECTS=$(ASMSOURCES:.asm=.o)
COBJECTS=$(SOURCES:.c=.o)

%.o: %.c
	$(GCC) $(GCCFLAGS) -I ../libraries/include -c _loader.c $(SOURCES) $(LIBRARYSOURCES) -pedantic -ansi -Wall

%.o: %.asm
	$(ASM) $(ASMFLAGS) $< -o $@

all: $(MODULE)

$(MODULE): $(ASMOBJECTS) $(COBJECTS) $(LIBRARYOBJECTS)
	$(LD) -T consumer.ld _loader.o $(COBJECTS) $(ASMOBJECTS) $(LIBRARYOBJECTS) -o ../$(MODULE)

clean:
	rm -rf *.o

.PHONY: all clean
