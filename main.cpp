#include <stm32f411xe.h>

extern "C" void delay(volatile uint32_t count) {
    while (count--) {
        __asm volatile ("nop");
    }
}

extern "C" int main() {
  
  RCC->AHB1ENR |= 1;
  const uint8_t port_number = 10;
  const uint8_t bit_number = port_number * 2;
  GPIOA->MODER |= (1ul << bit_number);
  GPIOA->MODER &= ~(1ul << (bit_number + 1));

  while (1) {
    GPIOA->ODR ^= (1ul << port_number);
    delay(500000);
  }
  return 0;
}
