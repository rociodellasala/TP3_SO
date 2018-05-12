include ../Makefile.inc

MODULE=consumer.bin
ASMSOURCES= $(wildcard asm/*.asm)
SOURCES=$(wildcard [^_]*.c)
ASMOBJECTS=$(ASMSOURCES:.asm=.o)
COBJECTS=$(SOURCES:.c=.o)

%.o: %.c
	$(GCC) $(GCCFLAGS) -I./include -c _loader.c $(SOURCES) -pedantic -ansi -Wall

%.o: %.asm
	$(ASM) $(ASMFLAGS) $< -o $@

all: $(MODULE)

$(MODULE): $(ASMOBJECTS) $(COBJECTS)
	$(LD) -T consumer.ld _loader.o $(COBJECTS) $(ASMOBJECTS) -o ../$(MODULE)

clean:
	rm -rf *.o

.PHONY: all clean
