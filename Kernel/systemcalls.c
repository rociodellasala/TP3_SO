#include <interrupts.h>
#include <keyboard_driver.h>
#include <time.h>
#include <types.h>
#include <video_driver.h>
#include <scheduler.h>
#include <heap.h>
#include <converter.h>

typedef qword (*sys)(qword rsi, qword rdx, qword rcx, qword r8, qword r9);

static sys sysCalls[12]; 

void sys_write(qword buffer, qword size, qword rcx, qword r8, qword r9) {
	print_char(buffer);
}

void sys_clear(qword rsi, qword rdx, qword rcx, qword r8, qword r9) {
	clear_screen();
}

void sys_read(qword file, qword buffer, qword size, qword r8, qword r9) {
	read_buffer((char*) buffer, (int) size);   
}

void sys_fontColor(qword color, qword rdx, qword rcx, qword r8, qword r9) {
	changeFontColor(color);  
}

void sys_nextLine(qword rsi, qword rdx, qword rcx, qword r8, qword r9) {
    	nextLine();
}

void sys_sleep(qword time, qword rdx, qword rcx, qword r8, qword r9){	
	sleep(time);
}

void sys_delete(qword rsi, qword rdx, qword rcx, qword r8, qword r9) {
	delete();
}

void sys_pixel(qword x, qword y, qword rcx, qword r8, qword r9) {
    	draw_pixel(x, y);
}

void sys_time(qword rsi, qword rdx, qword rcx, qword r8, qword r9) {
	printTime();
}

qword sys_malloc(qword size, qword rdx, qword rcx, qword r8, qword r9){
	void * pointer = malloc_heap(size);
	//nextLine();
	//nextLine();
	//print_string("Kernel: Se pidio ");
	//print_int(size);
	//nextLine();
	//print_string("Se retorna el puntero: ");
	//printHex(pointer);
	//nextLine();
	return (qword) pointer;
}

void sys_printHex(qword pointer, qword rdx, qword rcx, qword r8, qword r9){
	printHex(pointer);
}


void load_systemcalls(){
	sysCalls[1] = (sys)&sys_write;
	sysCalls[2] = (sys)&sys_clear;
	sysCalls[3] = (sys)&sys_read;
	sysCalls[4] = (sys)&sys_fontColor;
	sysCalls[5] = (sys)&sys_nextLine;
	sysCalls[6] = (sys)&sys_sleep;
	sysCalls[7] = (sys)&sys_delete;
	sysCalls[8] = (sys)&sys_pixel;
	sysCalls[9] = (sys)&sys_time;
	sysCalls[10] = (sys)&sys_malloc;
	sysCalls[11] = (sys)&sys_printHex;

	setup_IDT_entry(0x80, (qword)&_irq80Handler); 
}


qword syscall_handler(qword rdi,qword rsi, qword rdx, qword rcx, qword r8, qword r9) {
	if(rdi < 0 || rdi >= 12)
		return 0;
	
	return sysCalls[rdi](rsi,rdx,rcx,r8,r9);
}
