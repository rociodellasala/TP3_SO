#include <converter.h>
#include <interrupts.h>
#include <time.h>
#include <video_driver.h>

static unsigned long ticks = 0;

void timer_handler() {
	ticks++;
}

int ticks_elapsed() {
	return ticks;
}

int seconds_elapsed() {
	return ticks / 18;
}

void sleep(unsigned long t){
	_cli();
    
    unsigned long sleep_ticks = 0;
	while(sleep_ticks < t){
    		sleep_ticks++;
	}
	_sti();

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
