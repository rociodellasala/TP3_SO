include Makefile.inc

SAMPLE_DATA=shell.bin

all: terminal linearFDisp parabDisp 

terminal:
	cd shell; make

linearFDisp:
	cd linearGraph; make

parabDisp:
	cd parabolicGraph; make

clean:
	cd shell; make clean
	rm -rf *.bin


.PHONY: terminal all clean
