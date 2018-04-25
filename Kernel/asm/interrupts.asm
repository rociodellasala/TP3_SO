GLOBAL haltcpu

GLOBAL _cli
GLOBAL _sti

GLOBAL picMasterMask
GLOBAL picSlaveMask

GLOBAL _irq00Handler
GLOBAL _irq01Handler
GLOBAL _irq02Handler
GLOBAL _irq03Handler
GLOBAL _irq04Handler
GLOBAL _irq05Handler

GLOBAL _exception0Handler
GLOBAL _exception4Handler
GLOBAL _exception6Handler

GLOBAL _irq80Handler

EXTERN irqDispatcher
EXTERN syscall_handler
EXTERN exceptionDispatcher
EXTERN main

%include "./asm/macro.m"

SECTION .text

haltcpu:
	cli
	hlt
	ret


; -----------------------------------------------------------------------------
;	Clear Interrupts. The processor will not handle maskable interrupts.
;	Parameters:
;		None
; -----------------------------------------------------------------------------
_cli:
	cli
	ret



; -----------------------------------------------------------------------------
;	Set Interrupts. The processor will handle maskable interrupts.
;	Parameters:
;		None
; -----------------------------------------------------------------------------
_sti:
	sti
	ret



; -----------------------------------------------------------------------------
;	Set a Mask for the Master PIC. A device is disabled if the value of its bit
;	is 1.
;	Parameters:
;		-rdi: the mask applied.
; -----------------------------------------------------------------------------
picMasterMask:
	push 	rbp
    	mov	rbp, rsp

    	mov 	ax, di
    	out 	21h, al

    	pop 	rbp
    	retn



; -----------------------------------------------------------------------------
;	Set a Mask for the Slave PIC. A device is disabled if the value of its bit
;	is 1.
;	Parameters:
;		-rdi: the mask applied.
; -----------------------------------------------------------------------------
picSlaveMask:
	push 	rbp
    	mov 	rbp, rsp

    	mov 	ax, di  ; ax = mascara de 16 bits
    	out 	0A1h, al

    	pop 	rbp
    	retn



; -----------------------------------------------------------------------------
; 	8254 Timer (Timer Tick) interrupt.
; -----------------------------------------------------------------------------
_irq00Handler:
	irqHandlerMaster 0



; -----------------------------------------------------------------------------
; 	Keyboard interrupt.
; -----------------------------------------------------------------------------
_irq01Handler:
	irqHandlerMaster 1



; -----------------------------------------------------------------------------
; 	Cascade pic interrupt. (It is never used)
; -----------------------------------------------------------------------------
_irq02Handler:
	irqHandlerMaster 2



; -----------------------------------------------------------------------------
;	Serial Port 2 and 4 interrupt.
; -----------------------------------------------------------------------------
_irq03Handler:
	irqHandlerMaster 3



; -----------------------------------------------------------------------------
; 	Serial Port 1 and 3 interrupt.
; -----------------------------------------------------------------------------
_irq04Handler:
	irqHandlerMaster 4



; -----------------------------------------------------------------------------
;	USB interrupt.
; -----------------------------------------------------------------------------
_irq05Handler:
	irqHandlerMaster 5



; -----------------------------------------------------------------------------
;	Zero division exception.
; -----------------------------------------------------------------------------
_exception0Handler:
	exceptionHandler 0



; -----------------------------------------------------------------------------
;	Overflow exception.
; -----------------------------------------------------------------------------
_exception4Handler:
	exceptionHandler 4



; -----------------------------------------------------------------------------
;	Invalid opcode exception.
; -----------------------------------------------------------------------------
_exception6Handler:
	exceptionHandler 6



; -----------------------------------------------------------------------------
;	Syscall
; -----------------------------------------------------------------------------
_irq80Handler:
	call syscall_handler

	mov al, 20h
	out 20h, al

	iretq


SECTION .bss
	aux resq 1
