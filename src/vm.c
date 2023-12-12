/**
 * Main file for a Stack Based Virtual Machine (VM) written in C.
 * Copyright (C) 2023 Sergius Nyah
 * licensed under the MIT license.
*/

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "header.c"

#define STACK_SIZE 512 // (It remains a good practice to select powers of two 
                       //  for computational efficiency... 2^9 = 512)
typedef enum {
    PSH,  // Push unto STACK
    ADD,  // Addition Operation
    SUB,  // Subtraction Operation
    MUL,  // Multiplication Operation
    DIV,  // Division Operation
    MOD,  // Modulus Operation
    DUP,  // Duplicate the top of the STACK
    SWP,  // Swap the top two elements of the STACK
    OVR,  // Copy the second element of the STACK to the top
    POP,  // Pop the top of the STACK
    HLT,  // Halt the program
    EQ,   // Equality comparison
    LT,   // Less than comparison
    GT    // Greater than comparison
} InstructionSet;

int* load_program(const char* filename){
FILE* file = fopen(filename, "r");
if(!file){
    printf("Could not open file %s\n", filename);
    exit(1);
}

int* program = malloc(STACK_SIZE* sizeof(int));
int i = 0 ; 

while(fscanf(file, "%d", &program[i])==1){
    i++;
}
fclose(file);
return program;
}

const int program[] = {  // Stack program flow
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
/**
 * The instruction pointer (ip) points to the current instruction being executed.
 * Incrementing its value means moving to the next instruction.
 * The stack pointer (sp) points to the top of the stack which is initially empty (-1)
*/
int sp = -1, ip = 0;
bool running = true; // Control flag for the main execution loop of the program. P
                    // Program runs as long as running = true; 
int stack[STACK_SIZE];

// Push value to stack.
void push(int value) {   
    if(sp < STACK_SIZE) {
        stack[++sp] = value;
    } else {
        printf("Stack Overflow\n");
        running = false; // Program terminates if stack is full. 
    }
}
// Pop value from stack.
void pop(){
    if(sp > -1) {
        stack[sp--];
    } else {
        printf("Stack Underflow\n");
        running = false; // Program terminates if stack is empty. 
    }
}
// Subtract function. 
void sub(){
    int a;
    int b;

    if (sp >= 1) {
        a = stack[sp];
        b = stack[sp - 1];
        sp -= 2;
        push(b - a);
    } 
   else {
        printf("Stack Underflow\n");
        running = false; // Program terminates if stack is empty.
    }
}

void mul() {
    stack[sp - 1] *= stack[sp];
    sp--;
}

void div() {
    if(stack[sp-1]!=0)
    {
    stack[sp - 1] /= stack[sp];
    sp--;
    }
    else {
        printf("Division by Zero\n");
        running= false; // Error. 
    }
}

void mod() {
    if(stack[sp - 1]!=0) {
        stack[sp - 1] %= stack[sp];
    sp--;
    }
    else{
        printf("Division by Zero\n"); // Error
        running= false;
    }
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

int main(int argc, char** argv){
    if(argc < 2){
        printf("Usage: %s <program>\n", argv[0]);
        return 1;
    }
    int* program = load_program(argv[1]);
    while (running){
        eval(fetch(program));
        ip++;
    }

    free(program);
    return 0;
}

