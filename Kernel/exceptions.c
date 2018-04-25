#include <video_driver.h>
#include <converter.h>
#include <exceptions.h>

#define ZERO_EXCEPTION_ID 0
#define OVERFLOW_EXCEPTION 4
#define INVALID_OPCODE 6

static char* registers[] = {" R15: ", " R14: ", " R13: ", " R12: ", " R11: ", " R10: ", " R9:  ", " R8:  "
					, " RSI: ", " RDI: ", " RBP: ", " RDX: ", " RCX: ", " RBX: ", " RAX: ", " RIP: "};


void exceptionDispatcher(int exception, qword* rsp) {
	switch(exception){
		case ZERO_EXCEPTION_ID:
			zero_division(rsp);
			break;
		case OVERFLOW_EXCEPTION:
			overflow(rsp);
			break;
		case INVALID_OPCODE:
			invalid_opcode(rsp);
			break;
	}
}

static void zero_division(qword* rsp) {
	clear_screen();
	print_string("EXCEPTION 00: DIVIDE ERROR");
	nextLine();	
	showRegisters(rsp);
}

static void overflow(qword* rsp) {
	clear_screen();
	print_string("EXCEPTION 04: OVERFLOW");
	nextLine();	
	showRegisters(rsp);
}

static void invalid_opcode(qword* rsp) {
	clear_screen();
	print_string("EXCEPTION 06: INVALID OPCODE");
	nextLine();	
	showRegisters(rsp);
}

void cycle(){
	int i = 0;
	while(i < 500000000)
		i++;	
}

void showRegisters(qword* rsp){
	for(int i = 0 ; i < 16 ; i++){
		print_string(registers[i]);
		printHex(rsp[i]);
		nextLine();	
	}
	
	print_string("Returning to main menu...");
	cycle();
}
