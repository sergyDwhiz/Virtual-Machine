#include <stdio.h>
#include "vm.h" 

int main() {
    // Initialize the virtual machine
    VM vm; // Create a virtual machine

    int main() {
        // Load and execute the program
        vm_init(&vm); // Initialize the virtual machine
        vm_load_program(&vm, "program.bin"); // Load the program as a binary file
        vm_execute(&vm); // Execute the program

        // Cleanup
        vm_cleanup(&vm);

        return 0; // success
    }
}

