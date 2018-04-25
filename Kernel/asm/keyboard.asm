GLOBAL _read_keyboard
section .text

; -----------------------------------------------------------------------------
;	Get the RAW data from the Keyboard.
;	Return:
;		-rax: the RAW data.
; -----------------------------------------------------------------------------
_read_keyboard:
	push rbp
	mov rbp, rsp

	in al,60h

	leave
	ret


