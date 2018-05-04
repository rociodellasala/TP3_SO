include Makefile.inc

SAMPLE_DATA=shell.bin

all: terminal linearFDisp parabDisp needMem

terminal:
	cd shell; make all

linearFDisp:
	cd linearGraph; make all

parabDisp:
	cd parabolicGraph; make all

needMem:
	cd needMemory; make all

clean:
	cd shell; make clean
	cd linearGraph; make clean
	cd parabolicGraph; make clean
	cd needMemory; make clean
	rm -rf *.bin


.PHONY: terminal all clean
