#include <stm32f411xe.h>
#include <array>

extern "C" void delay(volatile uint32_t count) {
  while (count--) {
    __asm volatile("nop");
  }
}

int main() {
  constexpr auto arr = std::array{1, 2, 3};

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
