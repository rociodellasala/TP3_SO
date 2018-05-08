#include "converter.h"
#include "exceptions.h"
#include "video_driver.h"

#define ZERO_EXCEPTION_ID 0
#define INVALID_OPCODE 6

#define WAIT 500000000

typedef void (*handler_t)(qword *);

handler_t exception_handler[] = {zero_divisionHandler, 0, 0, 0, 0, 0, invalid_opcodeHandler};
static char* registers[] = {" R15: ", " R14: ", " R13: ", " R12: ", " R11: ", " R10: ", " R9:  ", " R8:  "
					, " RSI: ", " RDI: ", " RBP: ", " RDX: ", " RCX: ", " RBX: ", " RAX: ", " RIP: "};


void exceptionDispatcher(int exception, qword * rsp){
	exception_handler[exception](rsp);
}

void zero_divisionHandler(qword * rsp){
	clear_screen();
	print_string("EXCEPTION 00: DIVIDE ERROR");
	nextLine();	
	showRegisters(rsp);
}

void invalid_opcodeHandler(qword * rsp){
	clear_screen();
	print_string("EXCEPTION 06: INVALID OPCODE");
	nextLine();	
	showRegisters(rsp);
}

void cycle(){
	int i = 0;
	while(i < WAIT)
		i++;	
}

void showRegisters(qword * rsp){
	int i;

	for(i = 0; i < 16; i++){
		print_string(registers[i]);
		printHex(rsp[i]);
		nextLine();	
	}
	
	print_string("Returning...");
	cycle();
}
