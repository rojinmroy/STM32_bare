// Declare main
extern void main(void);

void Reset_Handler(void);

// Vector table (must be at 0x08000000)
__attribute__((section(".vectors")))
void (*vector_table[])(void) = {
    (void (*)(void))0x20005000,  // Initial stack pointer (top of RAM)
    Reset_Handler,                /* Vector 1: Reset */
    // ... other interrupt vectors (can leave as NULL for now)
};

void Reset_Handler(void) {
    extern unsigned long _etext, _sdata, _edata, _sbss, _ebss;
    
    // Copy .data from FLASH to RAM
    unsigned long *src = &_etext;
    unsigned long *dst = &_sdata;
    while (dst < &_edata) {
        *dst++ = *src++;
    }
    
    // Zero .bss
    dst = &_sbss;
    while (dst < &_ebss) {
        *dst++ = 0;
    }
    
    main();
    while(1);
}
