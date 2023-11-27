#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "header.c"

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
    HLT,
    EQ, // Equality comparison
    LT, // Less than comparison
    GT  // Greater than comparison
} InstructionSet;

const int program[] = {
    PSH, 5,
    PSH, 5,
    EQ,
    POP,
    PSH, 5,
    PSH, 10,
    LT,
    POP,
    PSH, 20,
    PSH, 30,
    GT,
    POP,
    HLT
};

int ip = 0;
bool running = true;
int sp = -1;
int stack[512];

void sub() {
    stack[sp - 1] -= stack[sp];
    sp--;
}

void mul() {
    stack[sp - 1] *= stack[sp];
    sp--;
}

void div() {
    stack[sp - 1] /= stack[sp];
    sp--;
}

void mod() {
    stack[sp - 1] %= stack[sp];
    sp--;
}

void dup() {
    sp++;
    stack[sp] = stack[sp - 1];
}

void swap() {
    int temp = stack[sp];
    stack[sp] = stack[sp - 1];
    stack[sp - 1] = temp;
}

void over() {
    sp++;
    stack[sp] = stack[sp - 2];
}

int fetch() {
    return program[ip];
}

void eval(int instr) {
    switch (instr) {
        case HLT:
            running = false;
            break;
        case PSH:
            sp++;
            stack[sp] = program[++ip];
            break;
        case ADD:
            stack[sp - 1] += stack[sp];
            sp--;
            break;
        case SUB:
            sub();
            break;
        case MUL:
            mul();
            break;
        case DIV:
            div();
            break;
        case MOD:
            mod();
            break;
        case DUP:
            dup();
            break;
        case SWP:
            swap();
            break;
        case OVR:
            over();
            break;
        case POP:
            printf("%d\n", stack[sp]);
            sp--;
            break;
        case EQ:
            if (stack[sp - 1] == stack[sp]) {
                stack[sp - 1] = 1; // True
            } else {
                stack[sp - 1] = 0; // False
            }
            sp--;
            break;
        case LT:
            if (stack[sp - 1] < stack[sp]) {
                stack[sp - 1] = 1; // True
            } else {
                stack[sp - 1] = 0; // False
            }
            sp--;
            break;
        case GT:
            if (stack[sp - 1] > stack[sp]) {
                stack[sp - 1] = 1; // True
            } else {
                stack[sp - 1] = 0; // False
            }
            sp--;
            break;
        default:
            printf("Invalid instruction\n");
            running = false;
            break;
    }
}

int main() {
    while (running) {
        eval(fetch());
        ip++;
    }

    return 0;
}
