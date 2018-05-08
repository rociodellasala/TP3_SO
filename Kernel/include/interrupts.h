#ifndef INTERRUPS_H
#define INTERRUPS_H

#include "types.h"

/* */
void _irq00Handler();
void _irq01Handler();
void _irq02Handler();
void _irq03Handler();
void _irq04Handler();
void _irq05Handler();

/* */
void _irq80Handler();

/* */
void _exception0Handler();
void _exception6Handler();

void setup_IDT_entry(int, qword);

/* */
void _cli();

/* */
void _sti();

/* */
void _hlt();

/* */
void picMasterMask(word);
void picSlaveMask(int *);

/* */
void load_idt();

/* */
void restoreContext();

/* */
void haltcpu();

#endif
