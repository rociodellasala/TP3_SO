#ifndef INTERRUPS_H
#define INTERRUPS_H

#include "types.h"

/* Handles interruption if ocurrs */
void _irq00Handler();
void _irq01Handler();
void _irq02Handler();
void _irq03Handler();
void _irq04Handler();
void _irq05Handler();

/* Handles syscall from userland if ocurrs */
void _irq80Handler();

/* Handles exception if ocurrs */
void _exception0Handler();
void _exception6Handler();

void setup_IDT_entry(int, qword);

void _cli();
void _sti();

void _hlt();

void picMasterMask(word);
void picSlaveMask(int *);

/* Loads IDT entries according to what we're going to use on our OS */
void load_idt();

/* Places the pointer to the stack of the next process to be executed */
void restoreContext();

void haltcpu();

#endif
