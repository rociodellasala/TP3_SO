include Makefile.inc

SAMPLE_DATA=shell.bin

all: terminal linearFDisp parabDisp needMem testMem back

terminal:
	cd shell; make all

linearFDisp:
	cd linearGraph; make all

parabDisp:
	cd parabolicGraph; make all

needMem:
	cd needMemory; make all

testMem:
	cd testMemoryManager; make all

back:
	cd background; make all

clean:
	cd shell; make clean
	cd linearGraph; make clean
	cd parabolicGraph; make clean
	cd needMemory; make clean
	cd testMemoryManager; make clean
	cd background; make clean
	rm -rf *.bin


.PHONY: terminal all clean
