typedef unsigned char uint8_t;
typedef unsigned int uint32_t;
typedef uint32_t size_t;


extern char __bss[], __bss_end[], __stack_top[];

void *memset(void *buf, char c, size_t n) {
    uint8_t *p = (uint8_t *) buf;
    while (n--)
        *p++ = c;
    return buf;
}

void kernel_main(void) {
    
    // Kim's Note
    // Basically what this is doing is 0-initilising a segment of memory that 
    // is used for uninitilised global and static variable
    memset(__bss, 0, (size_t) __bss_end - (size_t) __bss);

    for (;;);
}

__attribute__((section(".text.boot")))
__attribute__((naked))
void boot(void) {
    // Kim's Notes
    // Because the stack is growing towards 0, we want the top of the stack 
    // but you can imagine it as the bottom to make it make sense
    __asm__ __volatile__(
        "mv sp, %[stack_top]\n" // Set the stack pointer
        "j kernel_main\n"       // Jump to the kernel main function
        :
        : [stack_top] "r" (__stack_top) // Pass the stack top address as %[stack_top]
    );
}
