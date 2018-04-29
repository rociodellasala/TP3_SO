include Makefile.inc

SAMPLE_DATA=shell.bin

all: terminal linearFDisp parabDisp 

terminal:
	cd shell; make all

linearFDisp:
	cd linearGraph; make all

parabDisp:
	cd parabolicGraph; make

clean:
	cd shell; make clean
	cd linearGraph; make clean
	cd parabolicGraph; make clean
	rm -rf *.bin


.PHONY: terminal all clean
