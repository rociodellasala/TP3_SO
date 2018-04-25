#include <stdint.h>
#include <defs.h>
#include <interrupts.h>

#pragma pack(push)		/* Push de la alineación actual */
#pragma pack (1) 		/* Alinear las siguiente estructuras a 1 byte */

/* Descriptor de interrupcion */
typedef struct {
	  word offset_l;
	  word selector;
	  byte cero;
	  byte access;
	  word offset_m;
	  dword offset_h;
	  dword other_cero;
} DESCR_INT;

#pragma pack(pop)		/* Reestablece la alinceación actual */


/* IDT de 255 entradas */
DESCR_INT * idt = (DESCR_INT *) 0x0;

void load_idt() {
  	_cli();
	
	/* Cargo en la IDT las interrupciones */
  	setup_IDT_entry (0x20, (qword)&_irq00Handler);
  	setup_IDT_entry (0x21, (qword)&_irq01Handler);  

	/* Cargo en la IDT las excepciones */  	
	setup_IDT_entry (0x00, (qword)&_exception0Handler);
	setup_IDT_entry (0x04, (qword)&_exception4Handler);
	setup_IDT_entry (0x06, (qword)&_exception6Handler);


	picMasterMask(0xFC); 
	picSlaveMask(0xFF);
        
	_sti();
}

void setup_IDT_entry (int index, qword offset) {
	  idt[index].selector = 0x08;
	  idt[index].offset_l = offset & 0xFFFF;
	  idt[index].offset_m = (offset >> 16) & 0xFFFF;
	  idt[index].offset_h = (offset >> 32) & 0xFFFFFFFF;
	  idt[index].access = ACS_INT;
	  idt[index].cero = 0;
	  idt[index].other_cero = (dword) 0;
}
