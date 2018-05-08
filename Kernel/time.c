#include "interrupts.h"
#include "time.h"
#include "video_driver.h"

void enableTickInter(){
	picMasterMask(0xFC);
}

void disableTickInter(){
	picMasterMask(0x01);
}

void calculateTime(int * h, int * m, int * s){
	*h = hour();
	*m = minutes();
	*s = seconds();

	if(*h == 1)
		*h = 22;
	else if(*h == 2)
		*h = 23;
	else if(*h == 0)
		*h = 21;
	else
		*h = *h - 3;
}

void displayTime(int h, int m, int s){
	if(h < 10)
		print_string("0");
	
	print_int(h);
	print_string(":");
	
	if(m < 10)
		print_string("0");
	
	print_int(m);
	print_string(":");
	
	if(s < 10)
		print_string("0");
	
	print_int(s);
}

void printTime() {
	int h,m,s; 

	nextLine();
	calculateTime(&h,&m,&s);
	print_string("Local time is: ");
	displayTime(h, m, s);
}
