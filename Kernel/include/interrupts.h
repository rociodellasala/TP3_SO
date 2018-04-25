#ifndef INTERRUPS_H_
#define INTERRUPS_H_

#include "types.h"

void _irq00Handler(void);
void _irq01Handler(void);
void _irq02Handler(void);
void _irq03Handler(void);
void _irq04Handler(void);
void _irq05Handler(void);

void _irq80Handler(void);

void _exception0Handler(void);
void _exception4Handler(void);
void _exception6Handler(void);

void setup_IDT_entry(int index, qword handler);

void _cli(void);

void _sti(void);

void _hlt(void);

void picMasterMask(word);
void picSlaveMask(char*);

void load_idt();

//Termina la ejecución de la cpu.
void haltcpu(void);

#endif /* INTERRUPS_H_ */
