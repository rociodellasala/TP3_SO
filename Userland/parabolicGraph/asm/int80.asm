GLOBAL int80

%include "./asm/macros.m"

int80:

    pushRegisters
    INT 80h
    popRegisters
    ret
