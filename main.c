#define RCC_APB2ENR   (*(volatile unsigned int *)0x40021018)
#define GPIOC_CRH     (*(volatile unsigned int *)0x40011004)
#define GPIOC_ODR     (*(volatile unsigned int *)0x4001100C)

void main(void) {
    // Enable GPIOC clock
    RCC_APB2ENR |= (1 << 4);
    
    // Configure PC13 as output (LED on Bluepill)
    GPIOC_CRH |= (1 << 20);  // Mode = output
    GPIOC_CRH &= ~(3 << 22); // CNF = push-pull
    
    // Blink LED
    while(1) {
        GPIOC_ODR ^= (1 << 13);  // Toggle
        for(int i = 0; i < 1000000; i++);
    }
}
