include Makefile.inc

SAMPLE_DATA=shell.bin

all: terminal linearFDisp parabDisp testMem processR processW

terminal:
	cd shell; make all

linearFDisp:
	cd linearGraph; make all

parabDisp:
	cd parabolicGraph; make all

testMem:
	cd testMemoryManager; make all

processR:
	cd processRead; make all

processW:
	cd processWrite; make all

clean:
	cd shell; make clean
	cd linearGraph; make clean
	cd parabolicGraph; make clean
	cd testMemoryManager; make clean
	cd processRead; make clean
	cd processWrite; make clean
	rm -rf *.bin


.PHONY: terminal all clean
