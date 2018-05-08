#include "stack.h"
#include "structs.h"

void * fillStackFrame(void * entryPoint, void * baseStack){
	StackFrame * frame = (StackFrame*)baseStack - 1;
	frame->gs =	0x001;
	frame->fs =	0x002;
	frame->r15 = 0x003;
	frame->r14 = 0x004;
	frame->r13 = 0x005;
	frame->r12 = 0x006;
	frame->r11 = 0x007;
	frame->r10 = 0x008;
	frame->r9 =	 0x009;
	frame->r8 =	 0x00A;
	frame->rsi = 0x00B;
	frame->rdi = 0x00C;
	frame->rbp = 0x00D;
	frame->rdx = 0x00E;
	frame->rcx = 0x00F;
	frame->rbx = 0x010;
	frame->rax = 0x011;
	frame->rip = (qword)entryPoint;
	frame->cs =	 0x008;
	frame->eflags = 0x202;
	frame->rsp = (qword)&(frame->base);
	frame->ss = 0x000;
	frame->base = 0x000;

	return (void *) frame;	
}