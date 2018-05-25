include ../Makefile.inc

MODULE=libraries.bin
ASMSOURCES= $(wildcard asm/*.asm)
SOURCES=$(wildcard [^_]*.c)
ASMOBJECTS=$(ASMSOURCES:.asm=.o)
COBJECTS=$(SOURCES:.c=.o)

%.o: %.c
	$(GCC) $(GCCFLAGS) -I./include -c $(SOURCES) -pedantic -ansi -Wall

%.o: %.asm
	$(ASM) $(ASMFLAGS) $< -o $@

all: $(MODULE)

$(MODULE): $(ASMOBJECTS) $(COBJECTS)
	$(LD) -T libraries.ld $(COBJECTS) $(ASMOBJECTS)

clean:
	rm -rf *.o

.PHONY: all clean
