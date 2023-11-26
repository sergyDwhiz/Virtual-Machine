#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

typedef enum {
    PSH,
    ADD,
    SUB,
    MUL,
    DIV,
    MOD,
    DUP,
    SWP,
    OVR,
    POP,
    HLT
} InstructionSet;

int fetch();
void eval(int instr);
void sub();
void mul();
void div();
void mod();
void dup();
void swap();
void over();

#endif
