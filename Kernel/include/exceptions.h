#ifndef EXCEPTION_H
#define EXCEPTION_H

static void zero_division(qword * rsp);

static void overflow(qword * rsp);

static void invalid_opcode(qword * rsp);

void showRegisters(qword * rsp);

void cycle();


#endif
