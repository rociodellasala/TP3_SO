include Makefile.inc

SAMPLE_DATA=shell.bin

all: lib terminal linearFDisp parabDisp testMem processR processW back processRW processWR prod cons thread pA pB pC

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

back:
	cd background; make all

processRW:
	cd processReadAndWrite; make all

processWR:
	cd processWriteAndRead; make all

prod:
	cd producer; make all

cons:
	cd consumer; make all

thread:
	cd threadTest; make all

lib:
	cd libraries; make all

pA:
	cd proA; make all

pB:
	cd proB; make all

pC:
	cd proC; make all

clean:
	cd libraries; make clean
	cd shell; make clean
	cd linearGraph; make clean
	cd parabolicGraph; make clean
	cd testMemoryManager; make clean
	cd processRead; make clean
	cd processWrite; make clean
	cd processReadAndWrite; make clean
	cd processWriteAndRead; make clean
	cd background; make clean
	cd producer; make clean
	cd consumer; make clean
	cd threadTest; make clean
	cd proA; make clean
	cd proB; make clean
	cd proC; make clean
	rm -rf *.bin


.PHONY: terminal all clean
