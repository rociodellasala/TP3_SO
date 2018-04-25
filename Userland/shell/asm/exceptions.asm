GLOBAL divide_by_zero
GLOBAL overflow
GLOBAL invalid_opcode

; -----------------------------------------------------------------------------
;	Generates a divide by zero exception
;	Parameters:
;		None
; -----------------------------------------------------------------------------
divide_by_zero:
	push rbp
	mov rbp, rsp

	mov ax, 10
	mov bl, 0
	div bl

    	mov rsp, rbp
	pop rbp
	ret



; -----------------------------------------------------------------------------
;	Generates a overflow exception
;	Parameters:
;		None
; -----------------------------------------------------------------------------
overflow:
	push rbp
	mov rbp, rsp
	
	mov ecx, 2h
	mov eax, 4h
	idiv ecx
		

    	mov rsp, rbp
	pop rbp
	ret

	
; -----------------------------------------------------------------------------
;	Generates an invalid opcode exception
;	Parameters:
;		None
; -----------------------------------------------------------------------------
invalid_opcode:
	push rbp
	mov rbp, rsp

	UD2

    	mov rsp, rbp
	pop rbp
	ret




