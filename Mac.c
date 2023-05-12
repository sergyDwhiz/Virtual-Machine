#include<stdio.h>
#include<stdlib.h>
typedef enum {
    PSH,     // STACK operations. 
    ADD,
    POP,
    SET,
    HLT
} InstructionSet;

// Test program for Stack operations 

const int program[] = {
    PSH, 5,  // Pushes 5 to the stack (stores 5 in memory)
    PSH, 6,  // Pushes 6 to the stack (stores 6 in memory)
    ADD,     // performs the "ADD" function
    POP,     // Prints the result "11"
    HLT
};

int ip = 0;  // Sets instruction pointer to zero. 
            // IP serves as an index in the array as to 
            // which instruction is currently being executed.
int main() {
    int instr = program[ip];
    return 0;
}
// An indirect way to print the "instr" variable
int fetch() {
    return program[ip];  // prints "0"
}
// Prints the next instruction 

int main() {
    int x = fetch(); // PSH
    ip++; // increment instruction pointer
    int y = fetch(); // 5
}

// An automated version of the above function 
#include <stdbool.h> 

bool running = true;

int main() {
    while (running) {
       int x = fetch();
       if (x == HLT) running = false;
       ip++;
    }
}