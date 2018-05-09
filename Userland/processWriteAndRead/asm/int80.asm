section .text
GLOBAL int80

; -----------------------------------------------------------------------------
;	Enables Userland function to make system calls to the Kernel
;	Parameters:
;		Depends on the command invoked.
; -----------------------------------------------------------------------------
int80:
	
	push rbp
	mov rbp,rsp

	int 80h

	mov rsp,rbp
	pop rbp
	ret
