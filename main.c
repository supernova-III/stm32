#include <stm32f411xe.h>

static void delay(volatile uint32_t count) {
    while (count--) {
        __asm volatile ("nop");
    }
}

int main() {
    RCC->AHB1ENR |= (1 << 0);

    /* Настраиваем PA5 как выход (01b в MODER5) */
    GPIOA->MODER &= ~(3UL << (5 * 2)); // очистить
    GPIOA->MODER |=  (1UL << (5 * 2)); // выставить 01

    while (1) {
        /* Инвертируем бит 5 */
        GPIOA->ODR ^= (1 << 5);

        /* Задержка */
        delay(500000);
    }
  return 0;
}
