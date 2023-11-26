// Examines output from header & virtual files.
#include <stdio.h>
#include "src/vm.h"

int main() {
    // Initialize the virtual machine
    VM vm;
    vm_init(&vm);

    // Load and execute the program
    vm_load_program(&vm, "program.bin");
    vm_execute(&vm);

    // Cleanup
    vm_cleanup(&vm);

    return 0;
}